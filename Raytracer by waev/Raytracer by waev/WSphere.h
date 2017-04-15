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

	virtual int Intersection(WRay &ray, float &dist, WShadingInfo &ws);
	virtual bool shadowHit(WRay &r, float &tmin);
	virtual void minXYZ(float &mx, float &my, float &mz);
	virtual void maxXYZ(float &mx, float &my, float &mz);
};

