#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct { int x; int y; } Point;

char* read_file(const char*, char**);
void write_file(const char*, const char*, char**);
void write_point(char*, Point, char**);
Point read_point(const char*, char**);
void _error_message(char*, char**);
void _handle_error(char**);

int main(int argc, char** argv){
	if(argc != 4){
		return EXIT_FAILURE;
	}
	
	char** error = NULL;

	char* string = read_file(argv[1], error);
	if(error != NULL){
		_handle_error(error);
		return EXIT_FAILURE;
	}
	write_file(argv[2], string, error);
	if(error != NULL){
		_handle_error(error);
		return EXIT_FAILURE;
	}

	Point p = {.x = 3, .y = 14};
	write_point(argv[3], p, error);
	if(error != NULL){
		_handle_error(error);
		return EXIT_FAILURE;
	}

	Point q = read_point(argv[3], error);
	if(error != NULL){
		_handle_error(error);
		return EXIT_FAILURE;
	}
	printf("x: %d y: %d\n", q.x, q.y);

	free(string);
	free(error);
	return 0;
}

char* read_file(const char* path, char** error){
	FILE* fp = fopen(path, "r");
	if(fp == NULL) {
		_error_message("read_file(..) failed to open file", error);
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	long int length = ftell(fp);
	rewind(fp);

	char* string = malloc(sizeof(*string) * (length + 1));
	if(string == NULL){
		_error_message("read_file(..) failed to alloc string", error);
		return NULL;
	}
	
	for(int i = 0; i < length; i++){
		size_t read_count = fread(&(string[i]), sizeof(*string), 1, fp);
		if(read_count != 1){
			_error_message("read_file(..) failed to read from file", error);
			return NULL;
		}
	}
	string[length] = '\0';
	fclose(fp);

	return string;
}

void write_file(const char* path, const char* contents, char** error){
	FILE* fp = fopen(path, "w");
	if(fp == NULL){
		_error_message("write_file(..) failed to open file", error);
		return;
	}
	rewind(fp);

	size_t written_count = fwrite(contents, sizeof(*contents), strlen(contents), fp);
	if(written_count != strlen(contents)){
		_error_message("write_file(..) failed to write to file", error);
		return;
	}
	fclose(fp);
}

void write_point(char* path, Point p, char** error){
	FILE* fp = fopen(path, "w");
	if(fp == NULL){
		_error_message("write_point(..) failed to open file", error);
		return;
	}
	size_t written_count = fwrite(&p, sizeof(Point), 1, fp);
	if(written_count != 1){
		_error_message("write_point(..) failed to write to file", error);
		return;
	}

	fclose(fp);
}

Point read_point(const char* path, char** error){
	FILE* fp = fopen(path, "r");
	Point p;
	if(fp == NULL){
		_error_message("read_point(..) failed to open file", error);
		return p;
	}
	size_t read_count = fread(&p, sizeof(p), 1, fp);
	if(read_count != 1){
		_error_message("read_point(..) failed to read struct from file", error);
		return p;
	}
	fclose(fp);

	return p;
}

void _error_message(char* message, char** error){
	if(error == NULL){
		*error = malloc(sizeof(**error) * (strlen(message) + 1));
		strcpy(*error, message);	
	}
}

void _handle_error(char** error){
	fprintf(stderr, "Error: %s\n", *error);
	free(error);
}

