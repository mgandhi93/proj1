#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle(void)
{
	v1 = Point(1, 0, -1);
	v2 = Point(0, 1, -1);
	v3 = Point(1, 1, -1);
	brdf = BRDF();
}

Triangle::Triangle(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, BRDF brdf, vector<Matrix> matrices) {
	v1.x = ax;
	v1.y = ay;
	v1.z = az;
	v2.x = bx;
	v2.y = by;
	v2.z = bz;
	v3.x = cx;
	v3.y = cy;
	v3.z = cz;
	this->brdf = brdf;
	this->matrices = matrices;
}

Triangle::Triangle(Point x, Point y, Point z, BRDF brdf, vector<Matrix> matrices) {
	v1 = x;
	v2 = y;
	v3 = z;
	this->brdf = brdf;
	this->matrices = matrices;
}

bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local) {

	worldToObj(ray);

	float a = v1.x - v2.x;
	float b = v1.y - v2.y;
	float c = v1.z - v2.z;
	float d = v1.x - v3.x;
	float e = v1.y - v3.y;
	float f = v1.z - v3.z;
	float g = ray.dir.x;
	float h = ray.dir.y;
	float i = ray.dir.z;
	float j = v1.x - ray.position.x;
	float k = v1.y - ray.position.y;
	float l = v1.z - ray.position.z;
	float beta;
	float gamma; 
	float t;
	float M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
	t = -((f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M);

	if (t < ray.t_min || t > ray.t_max) {
		objToWorld(ray);
		return false;
	}
	gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if (gamma < 0 || gamma > 1) {
		objToWorld(ray);
		return false;
	}
	beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if (beta < 0 || beta > 1 - gamma) {
		objToWorld(ray);
		return false;
	}

	*thit = t;
	Point intersectPoint = ray.position.add((ray.dir.scalar(t)));
	Vector normal = v2.subtract(v1).crossProduct(v3.subtract(v1));
	objToWorld(intersectPoint);
	objToWorld(normal);
	normal.normalize();
	Normal normal3 = Normal(normal.x, normal.y, normal.z);
	*local = LocalGeo(intersectPoint, normal3);
	objToWorld(ray);
	return true;
}

bool Triangle::intersectP(Ray& ray) {

	worldToObj(ray);

	float a = v1.x - v2.x;
	float b = v1.y - v2.y;
	float c = v1.z - v2.z;
	float d = v1.x - v3.x;
	float e = v1.y - v3.y;
	float f = v1.z - v3.z;
	float g = ray.dir.x;
	float h = ray.dir.y;
	float i = ray.dir.z;
	float j = v1.x - ray.position.x;
	float k = v1.y - ray.position.y;
	float l = v1.z - ray.position.z;
	float beta;
	float gamma; 
	float t;
	float M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
	t = 0-((f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M);

	if (t < ray.t_min || t > ray.t_max) {
		//adding objToWorld(ray) here ruins the triangle images for some reason.
		return false;
	}
	gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if (gamma < 0 || gamma > 1) {
		objToWorld(ray);
		return false;
	}
	beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if (beta < 0 || beta > 1 - gamma) {
		objToWorld(ray);
		return false;
	}
	objToWorld(ray);
	return true;
}

void Triangle::getBRDF(LocalGeo& local, BRDF* brdf) {
	*brdf = this->brdf;
}

void Triangle::getMatrices(vector<Matrix>* matrices) {
	*matrices = this->matrices;
}

void Triangle::worldToObj(Ray &ray) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				iter.invert();
				ray.position = iter.multiply(ray.position);
				ray.dir = iter.multiply(ray.dir);
		}
	}
}

void Triangle::objToWorld(Ray& ray) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				ray.position = iter.multiply(ray.position);
				ray.dir = iter.multiply(ray.dir);
		}
	}
}

void Triangle::objToWorld(Point& intersectPoint) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				intersectPoint = iter.multiply(intersectPoint);
		}
	}	
}

void Triangle::objToWorld(Vector& normal) {
	if (!matrices.empty()) {                              //trans crap
		for (std::vector<Matrix>::iterator it = matrices.begin() ; it != matrices.end(); ++it) {
			Matrix iter = (*it);
				iter.invert();
				iter.transpose();
				normal = iter.multiply(normal);
		}
	}
}