#include "WPlane.h"



WPlane::WPlane()
{
	normal = WVector3(1, 0, 0);
	offset = 0.0f;
}

WPlane::WPlane(WVector3 n, float f)
{
	normal = WVector3(n);
	offset = f;
}


WPlane::~WPlane()
{
}

int WPlane::Intersection(WRay r, float & dist)
{
	int returnValue = 0;
	float denom = normal.dot(r.getDirection());
	float q = 0.0f;

	if (denom < 0.000001) {
		return 0; //parallel
	}
	
	q = r.getOrigin().dot(normal);
	dist = (offset - q) / denom;
	
	if (dist >= 0) {
		return 2; // from back
	}
	else {
		return 1; // from front
	}
}
