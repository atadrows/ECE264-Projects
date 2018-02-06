#include<stdio.h>
#include<limits.h>
#include "maze.h"

void _print_maze(Maze* maze);

int main (int argc, char** argv){
	Maze* maze = malloc_maze(6,7);
	free_maze(maze);

	FILE* fp = fopen("example_maze", "r");
	
	if(fp != NULL){
		// Test read_maze
		Maze* maze1 = read_maze(fp);

		printf("rows: %d cols: %d\n", maze1->num_rows, maze1->num_cols);
		_print_maze(maze1);
		
		// Test write_maze
		write_maze("test_write_maze.txt", maze1);

		printf("--------------------------------------\n");
	
		//Test make_taller
		Maze* maze2 = make_taller(maze1);
		_print_maze(maze2);

		printf("--------------------------------------\n");

		Maze* maze3 = make_wider(maze1);
		_print_maze(maze3);


		free_maze(maze1);
		free_maze(maze2);
		free_maze(maze3);
	}

	fclose(fp);
}

void _print_maze(Maze* maze){
	for(int i = 0; i < maze->num_rows; i++){
		for(int j = 0; j < maze->num_cols; j++){
			fputc(maze->cells[i][j], stdout);
		}
		fputc('\n', stdout);
	}

}
