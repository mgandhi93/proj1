#pragma once
#include "Primitive.h"
#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include <vector>
using namespace std;

class AggregatePrimitive
{
public:
	AggregatePrimitive();
	AggregatePrimitive(vector<Primitive*> list);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void pushBack(Primitive* primitive);
	vector<Primitive*> list;
};

