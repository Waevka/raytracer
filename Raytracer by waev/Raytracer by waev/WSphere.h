#pragma once
#include "WVector3.h"
#include "WRay.h"

class WSphere
{
private:
	WVector3 origin;
	float radius;
public:
	WSphere();
	WSphere(WVector3 v, float r);
	~WSphere();

	std::string toString();

	int Intersect(WRay ray, float &dist);
};

