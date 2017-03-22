#pragma once
#include "WRay.h"

class WPlane
{	
	WVector3 normal;
	float offset;

public:
	WPlane();
	WPlane(WVector3 n, float f);
	~WPlane();

	int Intersection(WRay r, float &dist);

};

