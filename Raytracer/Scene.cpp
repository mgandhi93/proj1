#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"
#include "Sampler.h"
#include "Film.h"
#include "Sample.h"
#include "Ray.h"
#include "Color.h"
#include "Raytracer.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "AmbientLight.h"
#include "Triangle.h"
#include <cstdlib> 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


Scene::Scene(void) {
}

void Scene::render() {
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 1, &color);
		color.color[0] = min(color.color[0] * 255.0f, 255.0f);
		color.color[1] = min(color.color[1] * 255.0f, 255.0f);
		color.color[2] = min(color.color[2] * 255.0f, 255.0f);
		film.setPixel(sample.x, sample.y, color.color);
	}
	film.saveImage();
}

void Scene::test() {
	sampler = Sampler(200, 200);

	Point cameraPosition = Point(0, 0, 150);
	Point LL = Point(-50, -50, 50);
	Point LR = Point(50, -50, 50);
	Point UL = Point(-50, 50, 50);
	Point UR = Point(50, 50, 50);
	camera = Camera(cameraPosition, UL, UR, LL, LR, 200, 200);

	Matrix trans = Matrix();
	trans.translate(0, 10, 0);
	matrices.push_back(trans);

	raytracer = Raytracer();
	BRDF brdftriangle = BRDF(0, 0.1, 0.1, 0, 0.4, 0.4, 0, 0.8, 0.8, 1000, 0, 0, 0);
	BRDF brdfSphere = BRDF(0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.5, 0.5, 0.5, 20, 0.0, 0.0, 0.0);

	Triangle* triangle = new Triangle(0.0, 50.0, 0.0, -50.0, -50.0, 0.0, 50.0, -50.0, 0.0, brdftriangle, matrices);
	Sphere* sphere = new Sphere(0, 50, 0, 10, brdfSphere, matrices);
	Sphere* sphere2 = new Sphere(-50, -50, 0, 10, brdfSphere, matrices);
	Sphere* sphere3 = new Sphere(50, -50, 0, 10, brdfSphere, matrices);

	raytracer.aggregatePrimitive.pushBack(triangle);
	raytracer.aggregatePrimitive.pushBack(sphere);
	raytracer.aggregatePrimitive.pushBack(sphere2);
	raytracer.aggregatePrimitive.pushBack(sphere3);

	PointLight* pointLight = new PointLight(200, 200, 200, Color(0.7, 0.7, 0.7));
	DirectLight* directLight = new DirectLight(0, 0, -1, Color(0.4, 0.4, 0.4));

	raytracer.addLight(pointLight);
	raytracer.addLight(directLight);

	film = Film(200, 200);
}

void Scene::loadObj(const char *objFile){ 

	ifstream objFile2(objFile);
	string line;
    vector<string> objStuff;
	vector<Point> vertices;
	vector<Normal> normals;
    if (!objFile2) {
        cout << "There was an error opening the file.\n";
    }
    while( objFile2>>line ) {
        objStuff.push_back(line);
    }

	for (int i = 0; i < objStuff.size(); i++) {
		if (objStuff[i] == "v") {
			Point tempPoint = Point(atof(objStuff[i+1].c_str()), atof(objStuff[i+2].c_str()), atof(objStuff[i+3].c_str()));
			vertices.push_back(tempPoint);
			i = i + 3;
		}
		if (objStuff[i] == "vn") {
			Normal tempNormal = Normal(atof(objStuff[i+1].c_str()), atof(objStuff[i+2].c_str()), atof(objStuff[i+3].c_str()));
			normals.push_back(tempNormal);
			i = i + 3;
		}
		if (objStuff[i] == "f") {
			Triangle* tempTriangle = new Triangle(vertices[atof(objStuff[i+1].c_str())-1], vertices[atof(objStuff[i+2].c_str())-1], vertices[atof(objStuff[i+3].c_str())-1], brdf, matrices);
			raytracer.aggregatePrimitive.pushBack(tempTriangle);
			i = i + 3;
		}
	}
};

int main(int argc, char *argv[]) {
	Scene newScene = Scene();


	string line;
    string file[2000];
	ifstream myFile(argv[1]);
    if (!myFile) {
        cout << "There was an error opening the file.\n";
        return 0;
    }
    int i=0;
    while( myFile>>line ) {
        file[i]=line;
        i++;
    }
    for (int j=0;j<i;j++) {
		if (file[j] == "cam") {
			Point cameraPosition = Point(atof(file[j + 1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()));
			Point LL = Point(atof(file[j+4].c_str()), atof(file[j+5].c_str()), atof(file[j+6].c_str()));
			Point LR = Point(atof(file[j+7].c_str()), atof(file[j+8].c_str()), atof(file[j+9].c_str()));
			Point UL = Point(atof(file[j+10].c_str()), atof(file[j+11].c_str()), atof(file[j+12].c_str()));
			Point UR = Point(atof(file[j+13].c_str()), atof(file[j+14].c_str()), atof(file[j+15].c_str()));
			newScene.camera = Camera(cameraPosition, UL, UR, LL, LR, 200, 200);
			newScene.raytracer = Raytracer();
			newScene.brdf = BRDF();
			newScene.sampler = Sampler(200, 200);
			newScene.color = Color();
			newScene.film = Film(200, 200);
			j = j + 15;
		}

		if (file[j] == "sph") {
			Sphere* tempSphere = new Sphere(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()), atof(file[j+4].c_str()), newScene.brdf, newScene.matrices);
			newScene.raytracer.aggregatePrimitive.pushBack(tempSphere);
			j = j + 4;
		}

		if (file[j] == "tri") {
			Triangle* tempTriangle = new Triangle(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()), atof(file[j+4].c_str()), atof(file[j+5].c_str()), atof(file[j+6].c_str()), atof(file[j+7].c_str()), atof(file[j+8].c_str()), atof(file[j+9].c_str()), newScene.brdf, newScene.matrices);
			newScene.raytracer.aggregatePrimitive.pushBack(tempTriangle);
			j = j + 9;
		}

		if (file[j] == "ltp") {
			PointLight* tempPL = new PointLight(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()), Color(atof(file[j+4].c_str()), atof(file[j+5].c_str()), atof(file[j+6].c_str())));
			newScene.raytracer.addLight(tempPL);
			j = j + 6;
		}

		if (file[j] == "ltd") {
			DirectLight* tempDL = new DirectLight(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()), Color(atof(file[j+4].c_str()), atof(file[j+5].c_str()), atof(file[j+6].c_str())));
			newScene.raytracer.addLight(tempDL);
			j = j + 6;
		}

		if (file[j] == "lta") {
			newScene.raytracer.ambient = AmbientLight(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()));
			j = j + 3;
		}

		if (file[j] == "mat") {
			newScene.brdf = BRDF(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()), atof(file[j+4].c_str()), atof(file[j+5].c_str()), atof(file[j+6].c_str()), atof(file[j+7].c_str()), atof(file[j+8].c_str()), atof(file[j+9].c_str()), atof(file[j+10].c_str()), atof(file[j+11].c_str()), atof(file[j+12].c_str()), atof(file[j+13].c_str()));
			j = j + 13;
		}

		if (file[j] == "xft") {
			Matrix tempMatrix = Matrix();
			tempMatrix.translate(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()));
			newScene.matrices.push_back(tempMatrix);
			j = j + 3;
		}

		if (file[j] == "xfr") {
			Matrix tempMatrix = Matrix();
			tempMatrix.rotate(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()));
			newScene.matrices.push_back(tempMatrix);
			j = j + 3;
		}

		if (file[j] == "xfs") {
			//This is buggy
			Matrix tempMatrix = Matrix();
			tempMatrix.scale(atof(file[j+1].c_str()), atof(file[j+2].c_str()), atof(file[j+3].c_str()));
			newScene.matrices.push_back(tempMatrix);
			j = j + 3;
		}

		if (file[j] == "xfz") {
			vector<Matrix> blankMatrices;
			newScene.matrices.swap(blankMatrices);
		}
		
		if (file[j] == "obj") {
			newScene.loadObj(file[j + 1].c_str());
			j = j + 1;
		}

		//if (file[j] != "xfz" && file[j] != "xfs" && file[j] != "xfr" && file[j] != "xft" && file[j] != "mat" && file[j] != "lta" && file[j] != "ltd" && file[j] != "ltp" && file[j] != "tri" && file[j] != "sph" && file[j] != "cam" &&  file[j] != "\n") {
			//cout << "Unrecognized input\n";
		//}
	}


	//newScene.test();
	newScene.render();
	return 0;
}