#include "stdafx.h"
#include "Vector.h"
#include <math.h>

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(float a, float b, float c) {
			x = a;
			y = b;
			z = c;
}

Vector Vector::add (Vector operandVector) {
	Vector returnVector(x + operandVector.x, y + operandVector.y, z + operandVector.z);
	return returnVector;
}

Vector Vector::subtract (Vector operandVector) {
	Vector returnVector(x - operandVector.x, y - operandVector.y, z - operandVector.z);
	return returnVector;
}

Vector Vector::scalar (float a) {
	Vector returnVector = Vector(x * a, y * a, z * a);
	return returnVector;
}

Vector Vector::divide (float a) {
	Vector returnVector = Vector(x/a, y/a, z/a);
	return returnVector;
}

void Vector::normalize () {
	 float divider = sqrt((x * x) + (y * y) + (z * z));
	 if (divider != 0) {
		x = x/divider;
		y = y/divider;
		z = z/divider;
	}
}

float Vector::dotProduct(Vector operandVector) {
	float returnFloat = (x * operandVector.x) + (y * operandVector.y) + (z * operandVector.z);
	return returnFloat;
}


Vector Vector::crossProduct(Vector operandVector) {
	Vector returnVector(y*operandVector.z - z*operandVector.y, z*operandVector.x - x*operandVector.z, x*operandVector.y - y*operandVector.x);
	return returnVector;
}

float Vector::dotProduct(Normal operandNormal) {
	float returnFloat = (x * operandNormal.x) + (y * operandNormal.y) + (z * operandNormal.z);
	return returnFloat;
}

Vector Vector::addNormal(Normal operandNormal) {
	Vector returnVector = Vector(x + operandNormal.x, y + operandNormal.y, z + operandNormal.z);
	return returnVector;
}

Vector Vector::subNormal(Normal operandNormal) {
	Vector returnVector = Vector(x - operandNormal.x, y - operandNormal.y, z - operandNormal.z);
	return returnVector;
}