#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "MagiaSprite.h"

MagiaSprite::MagiaSprite(const char* filename){
	if(read(filename)){
		//printf("Read %s\n", filename);
		size = w*h*channels;
	}
	else{
		printf("Failed to read %s\n", filename);
	}
}

MagiaSprite::MagiaSprite(int w, int h, int channels): w(w), h(h), channels(channels){
	size = w*h*channels;
	data = new uint8_t[size];
}

MagiaSprite::MagiaSprite(const MagiaSprite& img): MagiaSprite(img.w, img.h, img.channels){
	memcpy(data, img.data, img.size);
}

MagiaSprite::~MagiaSprite(){
	stbi_image_free(data);
}

bool MagiaSprite::read(const char* filename){
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data !=NULL;
}

bool MagiaSprite::write(const char* filename){
	ImageType type = getFileType(filename);
	int success;

	switch(type){
		case PNG:
			success = stbi_write_png(filename, w, h, channels, data, w*channels);
			break;
		case BMP:
			success = stbi_write_bmp(filename, w, h, channels, data);
			break;
		case JPG:
			success = stbi_write_jpg(filename, w, h, channels, data, 100);
			break;
		case TGA:
			success = stbi_write_tga(filename, w, h, channels, data);
			break;
	}

	return success != 0;
}

ImageType MagiaSprite::getFileType(const char* filename){
	const char* ext = strrchr(filename, '.');

	if(ext != nullptr){
		if(strcmp(ext, ".png") == 0){
			return PNG;
		}else if(strcmp(ext, ".jpg") == 0){
			return JPG;
		}else if(strcmp(ext, ".bmp") == 0){
			return BMP;
		}else if(strcmp(ext, ".tga") == 0){
			return TGA;
		}
	}
	return PNG;
}

MagiaSprite& MagiaSprite::overlay(const MagiaSprite& source, int x, int y, const char* newFileName){
	// Check that overlay image is not bigger or will go past the canvas of the original image
	if(source.h > (h - y) || source.w > (w - y)){
		printf("Image is too large to overlay.\n");
		return *this;
	}

	if(source.channels >= channels){
		MagiaSprite newImage(w, h, source.channels);

		// Copy old image to image with the new amount of channels
		for(int currY = 0; currY < newImage.w; currY++){
			for(int currX = 0; currX < newImage.w; currX++){
				for(int currCh = 0; currCh < newImage.channels; currCh++){
					int newSubPixel = (currY * newImage.w * newImage.channels) + (currX * newImage.channels) + currCh;
					int oldSubPixel = (currY * w * channels) + (currX * channels) + currCh;
					if(currCh > (channels - 1)){
						newImage.data[newSubPixel] = 255;
					}else{
						newImage.data[newSubPixel] = data[oldSubPixel];
					} 
				}
			}
		}

		// Place new pixels into copy image.
		for(int currY = 0; currY < source.h; currY++){
			for(int currX = 0; currX < source.w; currX++){
				for(int currCh = 0; currCh < source.channels; currCh++){
					int newSubPixel = ((currY + y) * newImage.w * newImage.channels) + ((currX + x) * newImage.channels) + currCh;
					int oldSubPixel = (currY * source.w * source.channels) + (currX * source.channels) + currCh;
					
					newImage.data[newSubPixel] = source.data[oldSubPixel];
				}
			}
		}

		newImage.write(newFileName);
	}

	return *this;
}

MagiaSprite& MagiaSprite::extract(int xPos, int yPos, int newWidth, int newHeight, const char* newFileName){
	// Check that the extract size and location are not out of bounds
	if(((xPos + newWidth) > w) || (yPos + newHeight) > h){
		printf("Parameters exceed bounds of original image.\n");
		return *this;
	}

	MagiaSprite newImage(newWidth, newHeight, channels);

	//printf("newImage; h: %i, w: %i, ch: %i n: %s\n", newImage.h, newImage.w, newImage.channels, newFileName);

	for(int currY = 0; currY < newImage.h; currY++){
		for (int currX = 0; currX < newImage.w; currX++){
			for(int currCh = 0; currCh < newImage.channels; currCh++){
				int newSubPixel = (currY * newImage.w * newImage.channels) + (currX * newImage.channels) + currCh;
				int oldSubPixel = ((currY + yPos) * w * channels) + ((currX + xPos) * channels) + currCh;
				newImage.data[newSubPixel] = data[oldSubPixel];

			}
		}
	}

	newImage.write(newFileName);

	return *this;

}