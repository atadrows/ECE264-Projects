#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

void _handleError(char**);
void _errorMessage(char*, char**);

int main(int argc, char** argv){
	//printf("howdy");
	char* error = NULL;

	// Test read_bmp
	FILE* fp = fopen("airplane.bmp", "r");
	if(fp == NULL){
		_errorMessage("main(..) failed to open file", &error);
		_handleError(&error);
		return EXIT_FAILURE;
	}
	BMPImage* image = read_bmp(fp, &error);	
	fclose(fp);
	if(image == NULL){
		_handleError(&error);
		return EXIT_FAILURE;
	}
	
	// Test writing airplane to a file
	FILE* write_fp = fopen("write_file", "w");
	if(fp == NULL){
		_errorMessage("main(..) failed to open file", &error);
		_handleError(&error);
		return EXIT_FAILURE;
	}
	
	bool worked = write_bmp(write_fp, image, &error);
	if(!worked){
		_handleError(&error);
		free_bmp(image);
		return EXIT_FAILURE;
	}
	fclose(write_fp);

	// Test cropping an image	
	BMPImage* crop_image = crop_bmp(image, 0, 0, 500, 200, &error);
	FILE* crop_fp = fopen("cropped.bmp", "w+");
	if(crop_fp == NULL){
		_errorMessage("main(..) failed to open file", &error);
		_handleError(&error);
		free_bmp(image);
		return EXIT_FAILURE;
	}
	free_bmp(image);

	worked = write_bmp(crop_fp, crop_image, &error); 
	if(!worked){
		_handleError(&error);
		return EXIT_FAILURE;
	}
	fclose(crop_fp);
	free_bmp(crop_image);

	// Test check_bmp_header with corrupt image
	/*FILE* corrupt_fp = fopen("corrupt_airplanei.bmp", "r");
	if(fp == NULL){
		_errorMessage("main(..) failed to open file", &error);
		_handleError(&error);
		return EXIT_FAILURE;
	}
	BMPImage* corrupt_image = read_bmp(corrupt_fp, &error);	
	fclose(corrupt_fp);
	if(corrupt_image == NULL){
		_handleError(&error);
		return EXIT_FAILURE;
	}
	free_bmp(corrupt_image);*/

	printf("It worked!");

	return EXIT_SUCCESS;
}

void _errorMessage(char* message, char** error){
	if(*error == NULL){
		*error = malloc(sizeof(**error) * (strlen(message) + 1));
		strcpy(*error, message);	
	}
}

void _handleError(char** error){
	if(*error != NULL){
		fprintf(stderr, "Error: %s\n", *error);
		free(*error);
	}
}

