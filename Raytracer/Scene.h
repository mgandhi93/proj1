#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Sampler.h"
#include "Film.h"
#include "Sample.h"
#include "Ray.h"
#include "Color.h"
#include "Raytracer.h"
#include "BRDF.h"
#include "Matrix.h"

class Scene
{
public:
	Scene();
	Camera camera;
	Sampler sampler;
	Sample sample;
	Film film;
	Ray ray;
	Color color;
	Raytracer raytracer;
	BRDF brdf;
	float width;
	float height;
	void render();
	void test();
	vector<Matrix> matrices;
	void loadObj(const char* objFile);
};

