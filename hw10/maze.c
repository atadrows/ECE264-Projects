#include<stdlib.h>

#include "maze.h"

// Why does Snoop Dogg carry an umbrella?
// Answer at bottom

void _find_maze_dimensions(FILE *, int *, int *);

Maze* malloc_maze(int num_rows, int num_cols){
	Maze* maze = malloc(sizeof(*maze));
	if(maze == NULL){
		free(maze);
		return NULL;
	}
	maze->num_rows = num_rows;
	maze->num_cols = num_cols;
	
	maze->cells = malloc(num_rows * sizeof(maze->cells[0]));
	if(maze->cells == NULL){
		free(maze->cells);
		free(maze);
		return NULL;
	}
	for(int i = 0; i < num_rows; i++){
		maze->cells[i] = malloc(num_cols * sizeof(maze->cells[0][0]));
		if(maze->cells[i] == NULL){
			free_maze(maze);
			return NULL;
		}
	}
	return maze;
}

void free_maze(Maze* maze){
	for(int i = 0; i < maze->num_rows; i++){
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
} 

Maze* read_maze(FILE* fp){
	rewind(fp);
	int num_rows = 0, num_cols = 0;
	_find_maze_dimensions(fp, &num_rows, &num_cols);

	Maze* maze = malloc_maze(num_rows, num_cols);
	int c = 0, j = 0;
	for(int i = 0; (c = fgetc(fp)) != EOF;){
		if(c != '\n'){
			maze->cells[j][i] = (char) c;
			i++;
		} else if(c == '\n'){
			j++;
			i = 0;
		}
	}
	rewind(fp);
	return maze;
}

bool write_maze(const char* filename, const Maze* maze){
	FILE *fp = fopen(filename, "w");
	if(fp == NULL){
		return false;
	}

	for(int i = 0; i < maze->num_rows; i++){
		for(int j = 0; j < maze->num_cols; j++){
			fputc(maze->cells[i][j], fp);
		}
		fputc('\n', fp);
	}

	fclose(fp);
	return true;
}

Maze *make_taller(const Maze* orig){
	int num_rows = orig->num_rows * 2 - 1, num_cols = orig->num_cols;
	Maze *maze = malloc_maze(num_rows, num_cols);
	if(maze == NULL){
		return NULL;
	}

	maze->num_rows = num_rows;
	maze->num_cols = num_cols;

	// Copy orig into beginning of maze
	int i, j;
	for(i = 0; i < orig->num_rows; i++){
		for(j = 0; j < orig->num_cols; j++){
			maze->cells[i][j] = orig->cells[i][j];
		}
	}

	// Mirror orig
	j = 0;
	for(int row  = orig->num_rows - 2; row >= 0; row--){
		for(int col = 0; col < orig->num_cols; col++){
			maze->cells[i][j] = orig->cells[row][col];
			j++;
		}
		i++;
		j = 0;
	}

	return maze;
}

Maze *make_wider(const Maze* orig){
	int num_rows = orig->num_rows, num_cols = orig->num_cols * 2 - 1;
	Maze *maze = malloc_maze(num_rows, num_cols);
	if(maze == NULL){
		return NULL;
	}

	maze->num_rows = num_rows;
	maze->num_cols = num_cols;

	// Copy orig into beginning of maze
	int i, j;
	for(i = 0; i < orig->num_rows; i++){
		for(j = 0; j < orig->num_cols; j++){
			maze->cells[i][j] = orig->cells[i][j];
		}
	}

	// Mirror orig
	i = 0;
	for(int col  = orig->num_cols - 2; col >= 0; col--){
		for(int row = 0; row < orig->num_rows; row++){
			maze->cells[i][j] = orig->cells[row][col];
			i++;
		}
		j++;
		i = 0;
	}

	//Remove center walls
	int middle_col = num_cols / 2, middle_row = num_rows / 2;
	int loc = middle_col;
	while(loc > 0){
		int above = maze->cells[middle_row - 1][loc];
		int below = maze->cells[middle_row + 1][loc];
		int left = maze->cells[middle_row][loc - 1];
		int right = maze->cells[middle_row][loc + 1];

		if(above == PATH || below == PATH || (left == PATH && right == PATH)){
			maze->cells[middle_row][loc] = PATH;
			maze->cells[middle_row][2 * middle_col - loc] = PATH;
			break;
		}
		loc--;
	}

	return maze;
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

// Fo Drizzle

