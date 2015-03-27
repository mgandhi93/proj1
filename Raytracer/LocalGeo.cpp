#include "stdafx.h"
#include "LocalGeo.h"


LocalGeo::LocalGeo() {
	position = Point(0, 0, 0);
	normal = Normal(0, 0, 0);
}

LocalGeo::LocalGeo(Point position, Normal normal) {
	this->position = position;
	this->normal = normal;
}


