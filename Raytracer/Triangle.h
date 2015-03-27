#pragma once
#include "Primitive.h"
class Triangle: public Primitive
{
public: 
	Triangle(void);
	Triangle(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, BRDF brdf, vector<Matrix> matrices);
	Triangle(Point x, Point y, Point z, BRDF brdf, vector<Matrix> matrices);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
	void getMatrices(vector<Matrix>* matrices);
	Point v1, v2, v3;
	BRDF brdf;
	vector<Matrix> matrices;
	void worldToObj(Ray& ray);
	void objToWorld(Ray& ray);
	void objToWorld(Point& intersectPoint);
	void objToWorld(Vector& normal);

};



