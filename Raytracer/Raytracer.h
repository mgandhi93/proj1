#pragma once
#include "Ray.h"
#include "Color.h"
#include "LocalGeo.h"
#include "Light.h"
#include "AggregatePrimitive.h"
#include "AmbientLight.h"

class Raytracer
{
public:
	Raytracer(void);
	void trace(Ray& ray, float depth, Color* color);
	AggregatePrimitive aggregatePrimitive;
	float threshold;
	vector<Light*> lights;
	void addLight(Light* light);
	Color shading(Intersection intersection, BRDF brdf, Ray lray, Color lcolor, Ray ray);
	AmbientLight ambient;
};

