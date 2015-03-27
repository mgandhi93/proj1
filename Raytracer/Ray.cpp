#include "stdafx.h"
#include "Ray.h"
#include "Vector.h"
#include "Point.h"


Ray::Ray(void) {
	position = Point();
	dir = Vector();
	t_min = 0;
	t_max = 0;
}

Ray::Ray(Point position, Vector dir, float t_min, float t_max) {
	this->position = position;
	this->dir = dir;
	this->t_min = t_min;
	this->t_max = t_max;
}
