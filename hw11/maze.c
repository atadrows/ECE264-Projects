#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "maze.h"

Maze* _malloc_maze(int, int);
void _free_maze(Maze*);
Maze* _read_maze(FILE*);
bool _write_maze(const char*, const Maze*);
void _find_maze_dimensions(FILE*, int*, int*);
Maze* _malloc_maze(int, int);
static int _pathfinder(Maze*, int, int, int, int, int, char*, int*, char*);

static bool is_path(Maze *maze, int row, int col){
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}

int dfs_shortest_path_directions(char *maze_file, char *directions_file, Coord source, Coord destination){
	
	FILE *maze_fp = fopen(maze_file, "r");
	if (maze_fp == NULL) {
		return -1;
	}
	Maze *maze = _read_maze(maze_fp);
	fclose(maze_fp);
	if (maze == NULL) {
		return -1;
	}
	if(!(is_path(maze, source.row, source.col) && is_path(maze, destination.row, destination.col))){
		_free_maze(maze);
		return -1;
	}

	char* current_dirs = malloc(maze->n_row * maze->n_col * sizeof(char));
	char* best_dirs = malloc(maze->n_row * maze->n_col * sizeof(char));
	int best_count = 0;

	_pathfinder(maze, source.row, source.col, destination.row, destination.col, 0, current_dirs, &best_count, best_dirs);

	FILE* dir_fp = fopen(directions_file, "w");
	if(dir_fp == NULL){
		free(current_dirs);
		free(best_dirs);
		_free_maze(maze);
		return -1;
	}

	rewind(dir_fp);
	for(int i = 0; i < best_count; i++){
		fputc(best_dirs[i], dir_fp);
	}

	free(current_dirs);
	free(best_dirs);
	_free_maze(maze);

	fclose(dir_fp);

	return best_count;
}

static int _pathfinder(Maze *maze, int curr, int curc, int endr, int endc, int count, char* current_dirs, int* best_count, char* best_dirs){
	maze->maze_array[curr][curc] = VISITED;
	if (curr == endr && curc == endc && (count < *best_count || *best_count == 0)) { // reach the destination 
		*best_count = count;
		memcpy(best_dirs, current_dirs, count);
		return *best_count;
	}
	
	if (is_path(maze, curr-1, curc) || (curr-1 == endr && curc == endc) ) {
		current_dirs[count] = 'N';
		_pathfinder(maze, curr-1, curc, endr, endc, count+1, current_dirs, best_count, best_dirs);
	}
	if (is_path(maze, curr+1, curc) || (curr+1 == endr && curc == endc)) {
		current_dirs[count] = 'S';
		_pathfinder(maze, curr+1, curc, endr, endc, count+1, current_dirs, best_count, best_dirs);
	}
	if (is_path(maze, curr, curc+1) || (curr == endr && curc+1 == endc)) {
		current_dirs[count] = 'E';
		_pathfinder(maze, curr, curc+1, endr, endc, count+1, current_dirs, best_count, best_dirs);
	}
	if (is_path(maze, curr, curc-1) || (curr == endr && curc-1 == endc)) {
		current_dirs[count] = 'W';
		_pathfinder(maze, curr, curc-1, endr, endc, count+1, current_dirs, best_count, best_dirs);
	}
	maze->maze_array[curr][curc] = PATH;
	return -1;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file, Coord source, Coord destination){
	FILE* maze_fp = fopen(maze_file, "r");
	if (maze_fp == NULL){
		return -1;
	}
	Maze* maze = _read_maze(maze_fp);
	if(maze == NULL){
		_free_maze(maze);
		return -1;
	}
	Maze* vis_maze = _read_maze(maze_fp);
	fclose(maze_fp);
	if(vis_maze == NULL){
		return -1;
	}
	if(!(is_path(maze, source.row, source.col) && is_path(maze, destination.row, destination.col))){
		_free_maze(maze);
		return -1;
	}
	FILE* dir_file = fopen(directions_file, "r");
	if (dir_file == NULL){
		_free_maze(maze);
		return -1;
	}


	int cur_row = source.row;
	int cur_col = source.col;
	int c, count = 1;
	rewind(dir_file);
	while((c = fgetc(dir_file)) != EOF){
		vis_maze->maze_array[cur_row][cur_col] = VISITED;
		switch(c){
			case 'N': cur_row--;
					  break;
			case 'S': cur_row++;
					  break;
			case 'E': cur_col++;
					  break;
			case 'W': cur_col--;
					  break;
			default: _free_maze(maze);
					 _free_maze(vis_maze);
					 return -1;
		}
		if(!is_path(maze, cur_row, cur_col)){
			_free_maze(maze);
			_free_maze(vis_maze);
			return -1;
		}
		count++;
	}
	
	rewind(dir_file);
	// Write visited maze into file, and check that it wrote
	if(!_write_maze(visited_file, vis_maze)){
		_free_maze(maze);
		_free_maze(vis_maze);
		fclose(dir_file);
		return -1;
	}
	
	_free_maze(maze);
	_free_maze(vis_maze);
	fclose(dir_file);

	if(cur_row == destination.row && cur_col == destination.col){
		return count;
	}
	return -1;
}

Maze* _malloc_maze(int num_rows, int num_cols){
	Maze* maze = malloc(sizeof(*maze));
	if(maze == NULL){
		free(maze);
		return NULL;
	}
	maze->n_row = num_rows;
	maze->n_col = num_cols;
	
	maze->maze_array = malloc(num_rows * sizeof(maze->maze_array[0]));
	if(maze->maze_array == NULL){
		free(maze->maze_array);
		free(maze);
		return NULL;
	}
	for(int i = 0; i < num_rows; i++){
		maze->maze_array[i] = malloc(num_cols * sizeof(maze->maze_array[0][0]));
		if(maze->maze_array[i] == NULL){
			_free_maze(maze);
			return NULL;
		}
	}
	return maze;
}

void _free_maze(Maze* maze){
	for(int i = 0; i < maze->n_row; i++){
		free(maze->maze_array[i]);
	}
	free(maze->maze_array);
	free(maze);
} 

Maze* _read_maze(FILE* fp){
	rewind(fp);
	int num_rows = 0, num_cols = 0;
	_find_maze_dimensions(fp, &num_rows, &num_cols);

	Maze* maze = _malloc_maze(num_rows, num_cols);
	int c = 0, j = 0;
	for(int i = 0; (c = fgetc(fp)) != EOF;){
		if(c != '\n'){
			maze->maze_array[j][i] = (char) c;
			i++;
		} else if(c == '\n'){
			j++;
			i = 0;
		}
	}
	maze->n_row = num_rows;
	maze->n_col = num_cols;

	rewind(fp);
	return maze;
}

bool _write_maze(const char* filename, const Maze* maze){
	FILE *fp = fopen(filename, "w");
	if(fp == NULL){
		return false;
	}

	for(int i = 0; i < maze->n_row; i++){
		for(int j = 0; j < maze->n_col; j++){
			fputc(maze->maze_array[i][j], fp);
		}
		fputc('\n', fp);
	}

	fclose(fp);
	return true;
}

void _find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {
	rewind(fp);
	*a_num_rows = *a_num_cols = 0;
	
	int seen_new_line = 0;
	int c = 0;
	for(int i = 0; (c = fgetc(fp)) != EOF; i++){
		if(c == '\n'){
			(*a_num_rows)++;
			if(!seen_new_line){
				seen_new_line = 1;
				*a_num_cols = i;
			}
		}
	}
	rewind(fp);
}
