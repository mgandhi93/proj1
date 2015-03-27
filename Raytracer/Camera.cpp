#include "stdafx.h"
#include "Camera.h"
#include "Point.h"

Camera::Camera() {
	position = Point(0, 0, 0);
	UL = Point(0, 0, 0);
	UR = Point(0, 0, 0);
	LL = Point(0, 0, 0);
	LR = Point(0, 0, 0);
}


Camera::Camera(Point position, Point UL, Point UR, Point LL, Point LR, float width, float height) {
	this->position = position;
	this->UL = UL;
	this->UR = UR;
	this->LL = LL;
	this->LR = LR;
	this->width = width;
	this->height = height;
}

void Camera::generateRay(Sample& sample, Ray* ray) {
	Point p;
	float u = sample.x/width;
	float v = sample.y/height;
	p.x = (u * ((v * LR.x) + ((1 - v) * UR.x))) + ((1 - u) * ((v * LL.x) + ((1 - v) * UL.x))); 
	p.y = (u * ((v * LR.y) + ((1 - v) * UR.y))) + ((1 - u) * ((v * LL.y) + ((1 - v) * UL.y))); 
	p.z = (u * ((v * LR.z) + ((1 - v) * UR.z))) + ((1 - u) * ((v * LL.z) + ((1 - v) * UL.z))); 

	Vector vec = p.subtract(position);
	vec.normalize();

	*ray = Ray(position, vec, 1, 1000);
}