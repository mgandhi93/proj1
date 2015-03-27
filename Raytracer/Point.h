#pragma once
#include "Vector.h"

class Point
{
public:
	Point(void);
	Point(float x, float y, float z);
	Vector add(Point operandPoint);
	Vector subtract(Point operandPoint);
	Point add(Vector operandVector);
	Point subtract(Vector operandVector);
	float x, y, z;
};

