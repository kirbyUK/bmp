#include "bmp.h"
#include "bmp_rgbquad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

struct BMP* open_bmp(const char* filename)
{
	struct BMP* b = malloc(sizeof(struct BMP));

	FILE* f = fopen(filename, "rb");
	if(f == NULL)
	{
		free(b);
		fprintf(stderr, "Error opening file '%s': %s\n", filename,
			strerror(errno));
		return NULL;
	}

	// Check the signature is 4D42:
	fread(&b->sig, 2, 1, f);
	if(b->sig != 0x4D42)
	{
		free(b);
		fclose(f);
		fprintf(stderr, "Error opening file '%s': File is not a bitmap\n",
			filename);
		return NULL;
	}

	// Get the size of the file:
	fread(&b->size, 4, 1, f);

	// Skip the next two fields as they're both blank:
	fseek(f, 4, SEEK_CUR);

	// Get the offset to the image data:
	fread(&b->offset, 4, 1, f);

	// Read the size of the info header:
	fread(&b->infoheader_size, 4, 1, f);

	// Read the height and width:
	fread(&b->width, 4, 1, f);
	fread(&b->height, 4, 1, f);

	// Skip the number of planes (always 1):
	fseek(f, 2, SEEK_CUR);
	fread(&b->bits_per_pixel, 2, 1, f);

	// Read the compression used:
	fread(&b->compression, 4, 1, f);

	// Read the image size:
	fread(&b->img_size, 4, 1, f);

	// Read the pixels-per-metre in both x and y:
	fread(&b->x_pixels_per_metre, 4, 1, f);
	fread(&b->y_pixels_per_metre, 4, 1, f);

	// Read the number of colours and important colours:
	fread(&b->num_colours, 4, 1, f);
	fread(&b->important_colours, 4, 1, f);

	// Read the colour data if it exists:
	//<https://msdn.microsoft.com/en-us/library/windows/desktop/dd183562%28v=vs.85%29.aspx>
	if(b->num_colours != 0)
	{
		/*// Check if the height is positive (bottom-up DIB) or negative (top-down):
		fseek(f, (b->infoheader_size - 40), SEEK_CUR);
		if(b->height > 0)
		{
		}
		else
		{
		}*/
	}

	// Allocate the memory for the array of actual pixel data:
	b->data = malloc(sizeof(struct BMP_RGBQuad*) * b->height);
	for(int i = 0; i < b->height; i++)
		b->data[i] = malloc(sizeof(struct BMP_RGBQuad) * b->width);

	// Read the actual pixel data: 
	fseek(f, b->offset, SEEK_SET);
	// Check to see if the height is positive (bottom-up DIB) or negative (top-down):
	if(b->height > 0)
	{
		for(int i = (b->height - 1); i >= 0; i--)
		{
			for(int j = (b->width - 1); j >= 0; j--)
			{
				fread(&b->data[i][j].r, 1, 1, f);
				fread(&b->data[i][j].g, 1, 1, f);
				fread(&b->data[i][j].b, 1, 1, f);
			}
		}
	}

	fclose(f);
	return b;
}

void free_bmp(struct BMP* b)
{
	for(int i = 0; i < b->height; i++)
		free(b->data[i]);
	free(b->data);
	free(b);
}
