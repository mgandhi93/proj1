#pragma once
#include "Light.h"
class DirectLight: public Light
{
public:
	DirectLight(void);
	DirectLight(float x, float y, float z, Color color);
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
	Vector direction;
	Color color;
};

