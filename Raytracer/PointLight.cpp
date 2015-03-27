#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight(void) {
	position = Point(0, 0, 0);
	color = Color(0, 0, 0);
}

PointLight::PointLight(float x, float y, float z, Color color) {
	position = Point(x, y, z);
	this->color = color;
}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
	*lcolor = color;
	Vector lrayDir = position.subtract(local.position);
	lrayDir.normalize();
	*lray = Ray(local.position, lrayDir, 0.05, 1000);
}

