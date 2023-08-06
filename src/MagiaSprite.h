#include <stdint.h>
#include <cstdio>

#include "lib/stb/stb_image.h"
#include "lib/stb/stb_image_write.h"

enum ImageType{
	PNG, JPG, BMP, TGA
};

struct MagiaSprite{
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;

	MagiaSprite(const char* filename);
	MagiaSprite(int w, int h, int channels);
	MagiaSprite(const MagiaSprite& image);
	~MagiaSprite();

	bool read(const char* filename);
	bool write(const char* filename);

	ImageType getFileType(const char* filename);

	MagiaSprite& overlay(const MagiaSprite& source, int x, int y, const char* newFileName);
	MagiaSprite& extract(int xPos, int yPos, int newWidth, int newHeight, const char* newFileName);

};