#pragma once
class Normal
{
public:
	Normal();
	Normal(float x, float y, float z);
	float x, y, z;
	Normal scalar(float scalar);
	Normal normalize();
};

