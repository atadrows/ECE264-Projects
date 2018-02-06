#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if(argc != 5){
		return EXIT_FAILURE;
	}
	FILE* input = fopen(argv[1], "r");
	if(input == NULL){ return EXIT_FAILURE; }

	long asciiCount[256] = {0};
	create_ascii_count_array(input, asciiCount);
	
	FILE* output1 = fopen(argv[2], "w");
	print_ascii_array(output1, asciiCount);
	fclose(input);
	fclose(output1);

	FILE* output2 = fopen(argv[3], "w");
	Node* linked = NULL;
	linked = create_sorted_list(linked, asciiCount);
	print_node(output2, linked, &print_tree_node);
	fclose(output2);
	
	FILE* output3 = fopen(argv[4], "w");
	Node* top = build_tree(linked);	
	print_coded_values(output3, top->ptr, "", 1);
	fclose(output3);

	destroy_node(top, &destroy_tree_node);
	return EXIT_SUCCESS;
}
