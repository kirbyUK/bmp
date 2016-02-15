#ifndef BMP_RGBQUAD_H
#define BMP_RGBQUAD_H
#include <stdint.h>

struct BMP_RGBQuad
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t reserved;
};

// Prints the given RGBQuad:
char* str_rgbquad(struct BMP_RGBQuad q);

#endif
