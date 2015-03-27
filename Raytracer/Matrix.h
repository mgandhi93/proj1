#pragma once
#include "Vector.h"
#include "Point.h"
#include "Normal.h"
class Matrix
{
public:
	Matrix(void);
	float matrix[4][4];
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void transpose();
	void invert();
	Vector multiply(Vector vector);
	Point multiply(Point point);
	Normal multiply(Normal normal);
};

