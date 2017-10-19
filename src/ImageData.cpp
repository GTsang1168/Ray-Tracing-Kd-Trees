#include "ImageData.h"

ImageData::ImageData(int x, int y, int aliasing) {
	WIDTH = x;
	HEIGHT = y;
	setAliasing(aliasing);
	dataArray.resize(x * y);
}

ImageData::ImageData() {}

void ImageData::setPixel(int x, int y, Colour colour) {
	dataArray[y * WIDTH + x] = colour;
}

Colour ImageData::getPixel(int x, int y) {
	return dataArray[y * WIDTH + x];
}

int ImageData::getWidth() {
	return WIDTH;
}

int ImageData::getHeight() {
	return HEIGHT;
}
int ImageData::getAliasing() const
{
	return ALIASING;
}

void ImageData::setAliasing(int value)
{
	ALIASING = value;
}

