#include "stdafx.h"
#include "DirectLight.h"


DirectLight::DirectLight() {
	direction = Vector(0, 0, 0);
	color = Color(0, 0, 0);
}

DirectLight::DirectLight(float x, float y, float z, Color color) {
	direction = Vector(x, y, z);
	this->color = color;
}

void DirectLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
	*lcolor = color;
	Vector lrayDir = direction.scalar(-1);
	lrayDir.normalize();
	*lray = Ray(local.position, lrayDir, 0.05, 1000);
}
