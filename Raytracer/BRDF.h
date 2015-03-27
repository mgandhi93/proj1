#pragma once
#include "Color.h"

class BRDF
{
public:
	BRDF();
	BRDF(float kar, float kag, float kab, float kdr, float kdg, float kdb, float ksr, float ksg, float ksb, float ksp, float krr, float krg, float krb);
	Color kd, ks, ka, kr;
	float ksp;

};

