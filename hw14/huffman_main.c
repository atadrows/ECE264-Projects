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
	if(input == NULL){ 
		return EXIT_FAILURE; 
	}

	long asciiCount[256] = {0};
	create_ascii_count_array(input, asciiCount);
	fclose(input);

	Node* linked = NULL;
	linked = create_sorted_list(linked, asciiCount);
	
	FILE* output1 = fopen(argv[2], "w");
	Node* top = build_tree(linked);	
	print_coded_values(output1, top->ptr, "", 1);
	fclose(output1);

	FILE* output2 = fopen(argv[3], "w+");
	print_char_header(output2, top->ptr);
	fputc('0', output2);
	fseek(output2, 0L, SEEK_END);
	long length = ftell(output2);
	char* header = malloc(sizeof(*header) * (length + 1));
	if(header == NULL){ 
		return EXIT_FAILURE; 
	}
	rewind(output2);
	header[length] = '\0';
	fread(header, sizeof(*header), length, output2);
	fclose(output2);

	FILE* output3 = fopen(argv[4], "w");
	print_huffman_bits(output3, header);
	fclose(output3);

	destroy_node(top, &destroy_tree_node);
	free(header);
	return EXIT_SUCCESS;
}
