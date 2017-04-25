#pragma once
#include "WModel.h"
class WTrianglePlane :
	public WModel
{
public:
	WTrianglePlane(WVector3 &center, float width, float height);
	~WTrianglePlane();
private:
	WVector3 center;
	float width;
	float height;
};

