#include "bmp.h"
#include <stdio.h>

int main()
{
	struct BMP* b = open_bmp("sample/RED2.BMP");
	if(b != NULL)
	{
		printf("BITMAPFILEHEADER:\n");
		printf("Size: %d bytes\n", b->size);
		printf("Pixel offset: %d\n", b->offset);

		printf("\nBITMAPINFOHEADER:\n");
		printf("Size of header: %d\n", b->infoheader_size);
		printf("Dimensions: %dpx x %dpx\n", b->width, b->height);
		printf("Bits per pixel: %d\n", b->bits_per_pixel);
		printf("Compression: %d\n", b->compression);
		printf("Image size: %d\n", b->img_size);
		printf("Pixels-per-metre: %dpx x %dpx\n", b->x_pixels_per_metre,
			b->y_pixels_per_metre);
		printf("Number of colours: %d\n", b->num_colours);
		printf("Important colours: %d\n", b->important_colours);

		printf("\nData:\n");
		for(int i = 0; i < b->height; i++)
		{
			printf("%d:\t", i);
			for(int j = 0; j < b->width; j++)
				printf("#%02x%02x%02x ", b->data[i][j].r, b->data[i][j].g,
					b->data[i][j].b);
			printf("\n");
		}
		free_bmp(b);
		return 0;
	}
	return 1;
}
