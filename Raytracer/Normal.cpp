#include "stdafx.h"
#include "Normal.h"
#include <cmath>


Normal::Normal() {
	x = 0;
	y = 0;
	z = 0;
}

Normal::Normal(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Normal Normal::scalar(float scalar) {
	return Normal(x * scalar, y * scalar, z * scalar);
}

Normal Normal::normalize() {
	float divider = sqrt( (x * x) + (y * y) + (z * z));
	return Normal(x/divider, y/divider, z/divider);
}