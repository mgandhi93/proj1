#pragma once
#include "Sample.h"
class Sampler
{
public:
	Sampler();
	Sampler(float width, float height);
	float width, height;
	float x, y;
	bool getSample(Sample* sample);
	bool firstSample;
};

