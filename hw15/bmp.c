#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

void _error_message(char*, char**);

BMPImage* read_bmp(FILE* fp, char** error){ // Test in the morn
	rewind(fp);
	// Alloc BMPImage
	BMPImage* image = malloc(sizeof(*image));
	if(image == NULL){
		_error_message("read_bmp(..) failed to alloc BMPImage", error);
		return NULL;
	}

	// Read header from file
	size_t header_read_count = fread(&(image->header), sizeof(image->header), 1, fp);
	if(header_read_count != 1){
		_error_message("read_bmp(..) failed to read BMPImage header from file", error);
		free(image);
		return NULL;
	}
	
	// Check that header is not corrupt
	bool good_header = check_bmp_header(&(image->header), fp);
	if(!good_header){
		_error_message("read_bmp(..) header was corrupt", error);
		free(image);
		return NULL;
	}

	// Alloc data
	image->data = malloc(sizeof(*(image->data)) * (image->header.size - BMP_HEADER_SIZE));
	if(image->data == NULL){
		_error_message("read_bmp(..) failed to alloc BMPImage data", error);
		free(image);
		return NULL;
	}

	// Read data from file
	size_t data_read_count = fread(image->data, sizeof(*(image->data)), image->header.size - BMP_HEADER_SIZE, fp);
	if(data_read_count != image->header.size - BMP_HEADER_SIZE){
		_error_message("read_bmp(..) failed to read BMPImage data from file", error);
		free_bmp(image);
		return NULL;
	}

	return image;
}

bool check_bmp_header(BMPHeader* bmp_hdr, FILE* fp){
	if (bmp_hdr->type != 0x4d42 
			|| bmp_hdr->offset != BMP_HEADER_SIZE 
			|| bmp_hdr->dib_header_size != DIB_HEADER_SIZE 
			|| bmp_hdr->num_planes != 1 
			|| bmp_hdr-> compression != 0 
			|| bmp_hdr->num_colors != 0 
			|| bmp_hdr->important_colors != 0 
			|| bmp_hdr->bits_per_pixel != 24){
		return false;
	} 
	long int cur_pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	if (bmp_hdr->size != ftell(fp)){
		return false;
	}
	fseek(fp, cur_pos, SEEK_SET);

	int padding = bmp_hdr->width_px % 4;

	long int real_image_size_bytes = (bmp_hdr->width_px * 3 + padding) * bmp_hdr->height_px;
	if(real_image_size_bytes != bmp_hdr->image_size_bytes){
		return false;
	}
	
	return true;
}

bool write_bmp(FILE* fp, BMPImage* image, char** error){
	// Write header to file
	long int header_written = fwrite(&(image->header), sizeof(image->header), 1, fp);
	if(header_written != 1){
		_error_message("write_bmp(..) failed to write header to file", error);
		return false;
	}

	// Write data to file
	long int data_written = fwrite(image->data, image->header.image_size_bytes, 1, fp);
	if(data_written != 1){
		_error_message("write_bmp(..) failed to write data to file", error);
		return false;
	}
	
	return true; // Write succeeded
}

void free_bmp(BMPImage* image){
	if(image->data != NULL){
		free(image->data);
	}
	free(image);
}

BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error){
	// Alloc for header
	BMPImage* crop_image = malloc(sizeof(*crop_image));
	if(crop_image == NULL){
		_error_message("crop_bmp(..) failed to alloc header", error);
		return NULL;
	}
	// Change new header values
	crop_image->header = image->header; // This might not work
	crop_image->header.width_px = w;
	crop_image->header.height_px = h;
	int pad = w % 4;
	long int image_size = (w * 3 + pad) * h;
	crop_image->header.image_size_bytes = image_size;
	crop_image->header.size = image_size + BMP_HEADER_SIZE;

	// Alloc for image data
	crop_image->data = malloc(image_size * sizeof(*(crop_image->data)));
	if(crop_image->data == NULL){	
		_error_message("crop_bmp(..) failed to alloc image data", error);
		free(crop_image);
		return NULL;
	}

	long int im_W = image->header.width_px;
	long int im_H = image->header.height_px;
	long int start = ((3 * im_W + pad) * (im_H - y - h) + 3 * x);

	long int pos = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w*3; j++){
			crop_image->data[pos] = image->data[pos + start + i * (pad + im_W*3 - w*3)];
			pos++;
		}
		for(int p = 0; p < pad; p++){
			crop_image->data[pos++] = 0;
		}
	}

	return crop_image;
}

void _error_message(char* message, char** error){
	if(*error == NULL){
		*error = malloc(sizeof(**error) * (strlen(message) + 1));
		strcpy(*error, message);	
	}
}

