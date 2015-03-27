#pragma once
#include "Normal.h"
class Vector
{
public:
	public:
		float x, y, z;
		Vector();
		Vector(float a, float b, float c);
		Vector add (Vector operandVector);
		Vector subtract (Vector operandVector);
		float dotProduct(Vector operandVector);
		Vector crossProduct(Vector operandVector);
		Vector scalar (float a);
		Vector divide (float a);
		void normalize();
		float dotProduct(Normal operandNormal);
		Vector addNormal(Normal operandNormal);
		Vector subNormal(Normal operandNormal);
};

