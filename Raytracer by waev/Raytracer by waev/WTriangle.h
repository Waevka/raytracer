#pragma once
#include "WGeometricObject.h"
class WTriangle :
	public WGeometricObject
{
public:
	WVector3 v0;
	WVector3 v1;
	WVector3 v2;
	WVector3 normal;
	WTriangle();
	WTriangle(WVector3 v0, WVector3 v1, WVector3 v2);
	WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WColor c);
	~WTriangle();
	virtual int Intersection(WRay ray, float & dist);
};

