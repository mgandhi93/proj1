#include "stdafx.h"
#include "Film.h"
#include <stdio.h>
#include "CImg.h"
using namespace cimg_library;


Film::Film() {
	width = 0;
	height = 0;
    image.assign(100, 100, 1, 3);
}

Film::Film(float width, float height) {
	this->width = width;
	this->height = height;
	image.assign(width, height, 1, 3);
}

void Film::setPixel(float x, float y, float color[]) {
	image.draw_point(x, y, color);
}

void Film::saveImage() {
	image.save("file.bmp");
}