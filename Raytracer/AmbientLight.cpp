#include "stdafx.h"
#include "AmbientLight.h"


AmbientLight::AmbientLight() {
	color = Color(0, 0, 0);
}


AmbientLight::AmbientLight(float x, float y, float z) {
	color = Color(x, y, z);
}
