#include "stdafx.h"
#include <cmath>
#include "Matrix.h"

Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = 0;
		}
	}
}

void Matrix::translate(float x, float y, float z) {
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
	
	matrix[0][3] = x;
	matrix[1][3] = y;
	matrix[2][3] = z;
}

void Matrix::scale(float x, float y, float z) {
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	matrix[3][3] = 1;
}

void Matrix::rotate(float x, float y, float z) {
	float theta = sqrt((x * x) + (y * y) + (z * z));
	float nx = x/theta;
	float ny = y/theta;
	float nz = z/theta;
	matrix[0][0] = cos(theta) + (nx * nx) * (1 - cos(theta));
	matrix[0][1] = nx * ny * (1 - cos(theta)) - nz *sin(theta);
	matrix[0][2] = nx * nz * (1 - cos(theta)) + ny * sin(theta);
	matrix[1][0] = ny * nx * (1 - cos(theta)) + nz * sin(theta);
	matrix[1][1] = cos(theta) + (ny * ny) * (1 - cos(theta));
	matrix[1][2] = ny * nz * (1 - cos(theta)) - nx * sin(theta);
	matrix[2][0] = nz * nx * (1 - cos(theta)) - ny * sin(theta);
	matrix[2][1] = nz * ny * (1 - cos(theta)) + nx * sin(theta);
	matrix[2][2] = cos(theta) + (nz * nz) * (1 - cos(theta));
}

void Matrix::transpose() {
    for (int i = 0; i < 4; i++) {
       for (int j = i; j < 4; j++) {
           float tempMat = matrix[i][j];
           matrix[i][j] = matrix[j][i];
           matrix[j][i] = tempMat;
       }
    }
}

void Matrix::invert() {
	//translations
	if (matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 1 && matrix[3][3] == 1) {
		matrix[0][3] = (0 - matrix[0][3]);
		matrix[1][3] = (0 - matrix[1][3]);
		matrix[2][3] = (0 - matrix[2][3]);
	}
	//scales
	if (matrix[0][3] == 0 && matrix[1][3] == 0 && matrix[2][3] == 0 && matrix[3][3] == 1) {
		matrix[0][0] = 1.0f/matrix[0][0];
		matrix[1][1] = 1.0f/matrix[1][1];
		matrix[2][2] = 1.0f/matrix[2][2];
	}
	//rotations
	if (matrix[3][3] == 0) {
		transpose();
	}

}

Vector Matrix::multiply(Vector vector) {
	float x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z;
	float y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z;
	float z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z;
	return Vector(x, y, z);
}

Point Matrix::multiply(Point point) {
	float x = (matrix[0][0] * point.x) + (matrix[0][1] * point.y) + (matrix[0][2] * point.z) + matrix[0][3];
	float y = (matrix[1][0] * point.x) + (matrix[1][1] * point.y) + (matrix[1][2] * point.z) + matrix[1][3];
	float z = (matrix[2][0] * point.x) + (matrix[2][1] * point.y) + (matrix[2][2] * point.z) + matrix[2][3];
	return Point(x, y, z);
}

Normal Matrix::multiply(Normal normal) {
	float x = matrix[0][0] * normal.x + matrix[0][1] * normal.y + matrix[0][2] * normal.z;
	float y = matrix[1][0] * normal.x + matrix[1][1] * normal.y + matrix[1][2] * normal.z;
	float z = matrix[2][0] * normal.x + matrix[2][1] * normal.y + matrix[2][2] * normal.z;
	return Normal(x, y, z);
}