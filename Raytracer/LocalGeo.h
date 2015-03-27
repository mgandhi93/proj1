#pragma once
#include "Normal.h"
#include "Point.h"

class LocalGeo
{
public:
	LocalGeo();
	LocalGeo(Point position, Normal normal);
	Point position;
	Normal normal;
};

