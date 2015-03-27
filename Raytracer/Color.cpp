#include "stdafx.h"
#include "Raytracer.h"
#include "Color.h"
#include <cmath>
#include <iostream>

Color::Color() {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
}


Color::Color(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Color Color::multiply(Color operandColor) {
	return Color(color[0] * operandColor.color[0], color[1] * operandColor.color[1], color[2] * operandColor.color[2]);
}

Color Color::scalar(float scalar) {
	return Color(color[0] * scalar, color[1] * scalar, color[2] * scalar);
}

Color Color::add(Color operandColor) {
	return Color(color[0] + operandColor.color[0], color[1] + operandColor.color[1],color[2] + operandColor.color[2]);
}