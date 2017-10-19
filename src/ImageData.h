/**
\class ImageData
\brief Stores the pixel data of the image being rendered.

This class is used to store the data of the "film strip" with which a ray traced image is being stored into. This class contains the final
image within a 2D array of type Colour. Using the getPixel method, and a relevant image generation class, a image can be 
outputted into the required format.

\author Gavin Tsang
\date 16/02/2015
*/

#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

#include "Colour.h"

class ImageData
{
public:
	ImageData(int x, int y, int aliasing = 1);
    ImageData();
	void setPixel(int x, int y, Colour colour);
	Colour getPixel(int x, int y);
	int getWidth();
	int getHeight();

	int getAliasing() const;

private:
	void setAliasing(int value);
	int WIDTH, HEIGHT, ALIASING;
	std::vector<Colour> dataArray;
};

