// raytracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Vector hi(1, 2, 3);
	Vector ge(3, 4, 5);
	Vector ze = hi.scalar(3);
	cout << ze.y;
	return 0;
}

