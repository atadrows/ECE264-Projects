#include <stdio.h>
#include <stdlib.h>

#include "maze.h"

int main(int argc, char ** argv){
	FILE *fp = fopen("sample.2.7x9", "r");

	int a_num_rows = 0;
	int a_num_cols = 0;
	int opening_location = 0;
	int num_paths = 0;
	char loc_type = 0; 

	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	char *filename = argv[3];

	if(fp != NULL){
		find_maze_dimensions(fp, &a_num_rows, &a_num_cols);
		opening_location = find_opening_location(fp);
		num_paths = count_path_locations(fp);
		loc_type = get_location_type(fp, row, col);
	}

	printf("Rows: %d, Cols: %d, Opening Loc: %d, Num Paths: %d\n", a_num_rows, a_num_cols, opening_location, num_paths);

	if(loc_type == PATH){
		printf("Loc Type: Path");
	} else if (loc_type == WALL){
		printf("Loc Type: Wall");
	} else {
		printf("You fucked up");
	}

	int num = represent_maze_in_one_line(filename, fp);
	printf("\nNum: %d", num);
	
	fclose(fp);

	return 0;
}
