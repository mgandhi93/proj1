#pragma once
#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"
#include "Matrix.h"
#include <vector>
using namespace std;
class Primitive
{
public:
	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
	virtual void getMatrices(vector<Matrix>* matrices) = 0;
};

