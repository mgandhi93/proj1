#pragma once
#include "Light.h"

class PointLight: public Light
{
public:
	PointLight(void);
	PointLight(float x, float y, float z, Color color);
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
	Point position;
	Color color;
};

