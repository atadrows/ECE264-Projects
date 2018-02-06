#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

// What do you call a fake spaghetti?
// Answer at bottom

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {
	rewind(fp);
	*a_num_rows = *a_num_cols = 0;
	
	int seen_new_line = 0;
	char c = 0;
	for(int i = 0; (c = fgetc(fp)) != EOF; i++){
		if(c == '\n'){
			(*a_num_rows)++;
			if(!seen_new_line){
				seen_new_line = 1;
				*a_num_cols = i;
			}
		}
	}
}

int find_opening_location(FILE * fp) {
	rewind(fp);
	int i = 0;
	while(fgetc(fp) != PATH){
		i++;
	}
	return i;
}

int count_path_locations(FILE * fp) {
	rewind(fp);
	int i = 0;
	char c = 0;
	while((c = fgetc(fp)) != EOF){
		if(c == PATH){
			i++;
		}
	}
	return i;
}

char get_location_type(FILE * fp, int row, int col) {
	rewind(fp);
	char c = 0;
	while(row > 0 || col > -1){
		c = fgetc(fp);
		if(c == '\n'){
			row--;
		} else if(row == 0){
			col--;
		}
	}
	return c;
}

int represent_maze_in_one_line(char * filename, FILE * fp) {
	rewind(fp);
	char c = 0;
	int i = 0;
	FILE *one_line = fopen(filename, "w");
	
	if(one_line != NULL){
		while((c = fgetc(fp)) != EOF){
			if(c == WALL || c == PATH){
				fputc(c, one_line);
				i++;
			}
		}
	}else{
		return MAZE_WRITE_FAILURE;
	}

	fclose(one_line);

	return i;
}

// An impasta
