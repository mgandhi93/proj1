#include "stdafx.h"
#include "AggregatePrimitive.h"
#include <iostream>

using namespace std;


AggregatePrimitive::AggregatePrimitive() {
}


AggregatePrimitive::AggregatePrimitive(vector<Primitive*> list) {
	this->list = list;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in) {
	float nearestHit = ray.t_max + 1;
	Intersection nearestIntersection;
	LocalGeo* localgeo = &(*in).localGeo;
	int flag = 0;
	for (std::vector<Primitive*>::iterator it = list.begin() ; it != list.end(); ++it) {
		Primitive* prim = *it;
		if ((*prim).intersect(ray, thit, localgeo)) {
			if (*thit < nearestHit) {
				nearestHit = *thit;
				nearestIntersection.localGeo = *localgeo;
				nearestIntersection.primitive = prim;
				flag = 1;
			}
		}
	}
	if (flag == 1) {
		*thit = nearestHit;
		*in = nearestIntersection;
		return true;
	} else {
		return false;
	}
}

bool AggregatePrimitive::intersectP(Ray& ray) {
	int flag = 0;
	for (std::vector<Primitive*>::iterator it = list.begin() ; it != list.end(); ++it) {
		Primitive* prim = *it;
		if ((*prim).intersectP(ray)) {
			flag = 1;
		}
	}
	if (flag == 1) {
		return true;
	} else {
		return false;
	}
}

void AggregatePrimitive::pushBack(Primitive* primitive) {
	list.push_back(primitive);
}
