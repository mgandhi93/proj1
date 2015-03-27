#include "stdafx.h"
#include "Sphere.h"
#include <cmath>
#include <iostream>
#include "Vector.h"
using namespace std;

Sphere::Sphere() {
	center = Point(0, 0, 0);
	radius = 0;
	brdf.kd = Color(0, 0, 0);
	brdf.ka = Color(0, 0, 0);
	brdf.ks = Color(0, 0, 0);
	brdf.kr = Color(0, 0, 0);
}

Sphere::Sphere(float x, float y, float z, float radius, BRDF brdf, vector<Matrix> matrices) {
	center = Point(x, y, z);
	this->radius = radius;
	this->brdf.kd = brdf.kd;
	this->brdf.ka = brdf.ka;
	this->brdf.ks = brdf.ks;
	this->brdf.kr = brdf.kr;
	this->brdf.ksp = brdf.ksp;
	this->matrices = matrices;
}


bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local) {

	worldToObj(ray);

	float a = ray.dir.dotProduct(ray.dir);
	float b = 2 * (ray.dir.dotProduct(ray.position.subtract(center)));
	float c = ray.position.subtract(center).dotProduct(ray.position.subtract(center)) - (radius * radius);

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {                                                    //Might be problem with grazes
		objToWorld(ray);
		return false; 
	}

	float t1, t2, helper;
	if (discriminant == 0) {
		t1 = - 0.5 * b/a;
		t2 = - 0.5 * b/a;
	}

	if (b > 0) {
		helper = -0.5 * (b + sqrt(discriminant));
	} else {
		helper = -0.5 * (b - sqrt(discriminant));
	}

	t1 = helper/a;                                //used an idea from scratchapixel.com
	t2 = c/helper;
                          
	if (t1 < t2) {
		if (t1 < ray.t_min || t1 > ray.t_max) {
			objToWorld(ray);
			return false;
		}
			*thit = t1;
			Point intersectPoint = ray.position.add((ray.dir.scalar(t1)));
			Vector normal = intersectPoint.subtract(center);
			objToWorld(intersectPoint);
			objToWorld(normal);
			normal.normalize();
			Normal normal3 = Normal(normal.x, normal.y, normal.z);
			*local = LocalGeo(intersectPoint, normal3);
	} 
	else {
		if (t2 < ray.t_min || t2 > ray.t_max) {
			objToWorld(ray);
			return false;
		}
			*thit = t2;
			Point intersectPoint = ray.position.add((ray.dir.scalar(t2)));
			Vector normal = intersectPoint.subtract(center);
			objToWorld(intersectPoint);
			objToWorld(normal);
			normal.normalize();
			Normal normal3 = Normal(normal.x, normal.y, normal.z);
			*local = LocalGeo(intersectPoint, normal3);
	}
	objToWorld(ray);
	return true;
}

bool Sphere::intersectP(Ray& ray) {

	worldToObj(ray);

	float a = ray.dir.dotProduct(ray.dir);
	float b = 2 * (ray.dir.dotProduct(ray.position.subtract(center)));
	float c = ray.position.subtract(center).dotProduct(ray.position.subtract(center)) - (radius * radius);

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {                                                    //Might be problem with grazes
		objToWorld(ray);
		return false; 
	}

	float t1, t2, helper;
	if (discriminant == 0) {
		objToWorld(ray);
		return true;
	}

	if (b > 0) {
		helper = -0.5 * (b + sqrt(discriminant));
	} else {
		helper = -0.5 * (b - sqrt(discriminant));
	}

	t1 = helper/a;                                //used an idea from scratchapixel.com
	t2 = c/helper;
                          
	if (t1 < t2) {
		if (t1 < ray.t_min || t1 > ray.t_max) {
			objToWorld(ray);
			return false;
		}
	} 
	if (t2 < t1) {
		if (t2 < ray.t_min || t2 > ray.t_max) {
			objToWorld(ray);
			return false;
		}
	}
	objToWorld(ray);
	return true;
}

void Sphere::getBRDF(LocalGeo& local, BRDF* brdf) {
	*brdf = this->brdf;
};

void Sphere::getMatrices(vector<Matrix>* matrices) {
	*matrices = this->matrices;
}


void Sphere::worldToObj(Ray &ray) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				iter.invert();
				ray.position = iter.multiply(ray.position);
				ray.dir = iter.multiply(ray.dir);
		}
	}
}

void Sphere::objToWorld(Ray& ray) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				ray.position = iter.multiply(ray.position);
				ray.dir = iter.multiply(ray.dir);
		}
	}
}

void Sphere::objToWorld(Point& intersectPoint) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				intersectPoint = iter.multiply(intersectPoint);
		}
	}	
}

void Sphere::objToWorld(Vector& normal) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				iter.invert();
				iter.transpose();
				normal = iter.multiply(normal);
		}
	}
}
