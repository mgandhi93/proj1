#include "stdafx.h"
#include "Raytracer.h"
#include <cmath>
#include "Sphere.h"
#include "LocalGeo.h"
#include "Primitive.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Intersection.h"
#include "BRDF.h"
#include <iostream>
using namespace std;

Raytracer::Raytracer(void) {
	threshold = 10;
	ambient = AmbientLight(0, 0, 0);
}

void Raytracer::trace(Ray& ray, float depth, Color* color) {
	float thit;
	Intersection intersection;

	if (depth > threshold) {
		return;
	}

	if (!aggregatePrimitive.intersect(ray, &thit, &intersection)) {
		*color = Color(0, 0, 0);
	} else {

		BRDF brdf;
		intersection.primitive->getBRDF(intersection.localGeo, &brdf);

		*color = Color(ambient.color.color[0] * brdf.ka.color[0], ambient.color.color[1] * brdf.ka.color[1], ambient.color.color[2] * brdf.ka.color[2]);
		

	    for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it) {
			Ray lray;
			Color lcolor;
			Light* lig = *it;
			(*lig).generateLightRay(intersection.localGeo, &lray, &lcolor);

			if (aggregatePrimitive.intersectP(lray)) {
				continue;
			} 
			else {
				*color = (*color).add(shading(intersection, brdf, lray, lcolor, ray));
			}
		}

		if (brdf.kr.color[0] > 0.0f || brdf.kr.color[1] > 0.0f || brdf.kr.color[2] > 0.0f) {
			Color tempColor;
			Normal normal = intersection.localGeo.normal;
			Vector rayDir = ray.dir;

			Vector rRayDir = rayDir.subNormal(normal.scalar(rayDir.dotProduct(normal) * 2));
			Ray reflectRay = Ray(intersection.localGeo.position, rRayDir, 0.05, ray.t_max);
			trace(reflectRay, depth+1, &tempColor);
			*color = (*color).add(brdf.kr.multiply(tempColor));
		}
	}
}


void Raytracer::addLight(Light* light) {
	lights.push_back(light);
}

Color Raytracer::shading(Intersection intersection, BRDF brdf, Ray lray, Color lcolor, Ray ray) {
			Normal normal = intersection.localGeo.normal;

			Color Kdl = brdf.kd.multiply(lcolor);
			float dotProductln = max(lray.dir.dotProduct(normal), (float) 0.0);
			Color Kd = Kdl.scalar(dotProductln);

			Color Ksl = brdf.ks.multiply(lcolor);
			Vector rVec = lray.dir.scalar(-1).addNormal(normal.scalar(dotProductln * 2));
			Vector vVec = ray.position.subtract(intersection.localGeo.position);
			vVec.normalize();

			float dotProductrv = pow((max(rVec.dotProduct(vVec), (float) 0.0)), brdf.ksp);
			Color Ks = Ksl.scalar(dotProductrv);

			return Color(Kd.color[0] + Ks.color[0] + brdf.ka.color[0], Kd.color[1] + Ks.color[1] + brdf.ka.color[1], Kd.color[2] + Ks.color[2] + brdf.ka.color[2]);
}