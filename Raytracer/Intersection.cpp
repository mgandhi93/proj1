#include "stdafx.h"
#include "Intersection.h"


Intersection::Intersection() {
}

Intersection::Intersection(LocalGeo localGeo, Primitive& primitive1) {
	this->localGeo = localGeo;
	*primitive = primitive1;
}