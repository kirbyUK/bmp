#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct BMP* open_bmp(const char* filename)
{
	struct BMP* b = malloc(sizeof(struct BMP));

	FILE* f = fopen(filename, "rb");
	if(f == NULL)
	{
		free(b);
		return NULL;
	}

	// Check the signature is 4D42:
	fread(&b->sig, 2, 1, f);
	if(b->sig != 0x4D42)
	{
		free(b);
		fclose(f);
		return NULL;
	}

	// Get the size of the file:
	fread(&b->size, 4, 1, f);

	// Skip the next two fields as they're both blank:
	fseek(f, 4, SEEK_CUR);

	// Get the offset to the image data:
	fread(&b->offset, 4, 1, f);

	// Skip the size of BITMAPINFOHEADER (always 40):
	fseek(f, 4, SEEK_CUR);

	// Read the height and width:
	fread(&b->width, 4, 1, f);
	fread(&b->height, 4, 1, f);

	// With this, we can allocate the memory for the array of actual pixel data:
	b->data = malloc(sizeof(uint32_t*) * b->height);
	for(int i = 0; i < b->height; i++)
		b->data[i] = malloc(sizeof(uint32_t) * b->width);

	// Skip the number of planes (always 1):
	fseek(f, 2, SEEK_CUR);
	fread(&b->bits_per_pixel, 2, 1, f);

	// Read the actual pixel data: 
	fseek(f, b->offset, SEEK_SET);
	for(int i = 0; i < b->height; i++)
		fread(b->data[i], b->bits_per_pixel, b->width, f);

	fclose(f);
	return b;
}

void free_bmp(struct BMP* b)
{
	for(int i = 0; i < b->width; i++)
		free(b->data[i]);
	free(b->data);
	free(b);
}

int main()
{
	struct BMP* b = open_bmp("test.bmp");
	if(b != NULL)
	{
		printf("Size: %d bytes\n", b->size);
		printf("Dimensions: %dpx x %dpx\n", b->width, b->height);
		printf("Bits per pixel: %d\n", b->bits_per_pixel);

		printf("\nData:\n");
		for(int i = 0; i < b->height; i++)
		{
			printf("%d:\t", i);
			for(int j = 0; j < b->width; j++)
				printf("%x, ", b->data[i][j]);
			printf("\n");
		}
		free_bmp(b);
		return 0;
	}
	return 1;
}
