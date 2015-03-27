#pragma once
#include "LocalGeo.h"
#include "Primitive.h"
class Intersection
{
public:
	Intersection();
	Intersection(LocalGeo localGeo, Primitive& primitive1);
	LocalGeo localGeo;
	Primitive* primitive;
};

