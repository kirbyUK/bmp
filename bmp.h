#ifndef BMP_H
#define BMP_H
#include "bmp_rgbquad.h"
#include <stdint.h>

// A structure defining the bitmap:
// <https://msdn.microsoft.com/en-us/library/windows/desktop/dd183391%28v=vs.85%29.aspx>
// <http://www.fastgraph.com/help/bmp_header_format.html>
struct BMP
{
	// BITMAPFILEHEADER:
	// The filetype signature (must be 424D):
	uint16_t sig;

	// The size of the file (according to the header):
	uint32_t size;

	// The offset to the start of the image:
	uint32_t offset;

	// BITMAPINFOHEADER:
	// The image dimensions:
	int32_t width;
	int32_t height;

	// The number of bits per pixel:
	uint32_t bits_per_pixel;

	// RGBQUAD array:
	uint16_t** data;

	// Colour-index array:
	struct BMP_RGBQuad colours[];
};

// Opens a given bitmap file and returns a BMP struct:
struct BMP* open_bmp(const char* filename);

// Frees memory allocated by creating a BMP struct with open_bmp:
void free_bmp(struct BMP* b);

#endif
