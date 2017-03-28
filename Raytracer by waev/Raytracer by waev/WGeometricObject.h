#pragma once
#include "WColor.h"
#include "WRay.h"

class WGeometricObject
{
private:
	WColor color;
public:
	WGeometricObject(WColor c);
	~WGeometricObject();
	WColor getColor();
	virtual int Intersection(WRay ray, float & dist);
};

