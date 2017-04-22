#include "WSphericalMap.h"



WSphericalMap::WSphericalMap()
{
}


WSphericalMap::~WSphericalMap()
{
}

void WSphericalMap::getTexelCoordinates(WVector3 & localHitPoint, int hres, int vres, int & row, int & column)
{	
	WVector3 lhp(localHitPoint);
	lhp.normalize();
	float theta = acos(lhp.y);
	float phi = atan2(lhp.x, lhp.z);
	if (phi < 0.0) {
		phi += TWO_PI;
	}

	// map to (u, v)
	float u = phi * invTWO_PI;
	float v = 1 - theta * invPI;

	column = (int)((hres - 1)  * u);
	row = (int)((vres - 1) * v);
}
