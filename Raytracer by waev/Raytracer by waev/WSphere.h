#pragma once
#include "WVector3.h"
#include "WRay.h"
#include "WGeometricObject.h"

class WSphere : public WGeometricObject
{
private:
	WVector3 origin;
	float radius;
public:
	WSphere();
	WSphere(WVector3 v, float r, WColor c);
	~WSphere();

	std::string toString();

	int Intersection(WRay ray, float &dist, WShadingInfo &ws);
	bool shadowHit(WRay &r, float &tmin);
};

