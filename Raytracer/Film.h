#pragma once
#include "CImg.h"
using namespace cimg_library;

class Film
{
public:
	CImg<float> image;
	float width, height;
	void setPixel(float x, float y, float color[]);
	void saveImage();
	Film();
	Film(float width, float height);
};

