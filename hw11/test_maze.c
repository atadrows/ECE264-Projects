#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);
int _verify_decimal(char*);

int main(int argc, char* argv[]) 
{
	if (argc < 2) {
		return EXIT_FAILURE;
	}

	if(strcmp("-s", argv[1]) == 0){
		if(argc != 9){
			return EXIT_FAILURE;
		}
		char* maze_file = argv[2];
		char* directions_file = argv[3];
		char* visited_file = argv[4];

		Coord source, dest;
		source.row = _verify_decimal(argv[5]);
		source.col = _verify_decimal(argv[6]);
		dest.row = _verify_decimal(argv[7]);
		dest.col = _verify_decimal(argv[8]);

		if(source.row == -1 || source.col == -1 || dest.row == -1 || dest.col == -1){
			return EXIT_FAILURE;
		}

		int step_count = simulate_movement(maze_file, directions_file, visited_file, source, dest);
		printf("%d\n", step_count);
	} else if(strcmp("-m", argv[1]) == 0){
		if(argc != 8){
			return EXIT_FAILURE;
		}
		char* maze_file = argv[2];
		char* directions_file = argv[3];

		Coord source, dest;
		source.row = _verify_decimal(argv[4]);
		source.col = _verify_decimal(argv[5]);
		dest.row = _verify_decimal(argv[6]);
		dest.col = _verify_decimal(argv[7]);

		if(source.row == -1 || source.col == -1 || dest.row == -1 || dest.col == -1){
			return EXIT_FAILURE;
		}

		int step_count = dfs_shortest_path_directions(maze_file, directions_file, source, dest);
		printf("%d\n", step_count);

	}
	return EXIT_SUCCESS;
}

int _verify_decimal(char* str){
	int result = strtol(str, NULL, 10);

	if(result == 0 && strcmp("0", str) == 0){
		return 0;
	} else if(result == 0){
		return -1;
	}
	return result;
}
