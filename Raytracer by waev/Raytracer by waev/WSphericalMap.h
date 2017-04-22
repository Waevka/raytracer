#pragma once
#include "WMapping.h"
#define PI			3.1415926535897932384;
#define TWO_PI		6.2831853071795864769;
#define PI_ON_180	0.0174532925199432957;
#define invPI		0.3183098861837906715;
#define invTWO_PI	0.1591549430918953358;

class WSphericalMap :
	public WMapping
{
public:
	WSphericalMap();
	~WSphericalMap();
	virtual void getTexelCoordinates(WVector3 &localHitPoint,
		int hres, int vres, int &row, int &column);
};

