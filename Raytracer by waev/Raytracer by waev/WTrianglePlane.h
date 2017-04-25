#pragma once
#include "WModel.h"
class WTrianglePlane :
	public WModel
{
public:
	WTrianglePlane(WVector3 &center, float width, float height);
	~WTrianglePlane();
	virtual int Intersection(WRay &ray, float &dist, WShadingInfo &ws);
private:
	WVector3 center;
	float width;
	float height;
};

