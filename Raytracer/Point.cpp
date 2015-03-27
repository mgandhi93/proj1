#include "stdafx.h"
#include "Point.h"
#include "Vector.h"


Point::Point(void) {
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Point::add(Point operandPoint) {
	Vector returnVector = Vector(x + operandPoint.x, y + operandPoint.y, z + operandPoint.z);
	return returnVector;
}

Vector Point::subtract(Point operandPoint) {
	Vector returnVector = Vector(x - operandPoint.x, y - operandPoint.y, z - operandPoint.z);
	return returnVector;
}

Point Point::add(Vector operandVector) {
	Point returnPoint = Point(x + operandVector.x, y + operandVector.y, z + operandVector.z);
	return returnPoint;
}

Point Point::subtract(Vector operandVector) {
	Point returnPoint = Point(x - operandVector.x, y - operandVector.y, z - operandVector.z);
	return returnPoint;
}


