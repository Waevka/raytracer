#pragma once
#include "WVector3.h"

class WRay
{
private:
	WVector3 destination;
	float distance;
public:
	WVector3 origin;
	WVector3 direction;
	WRay();
	WRay(WVector3 &o, WVector3 &d);
	~WRay();

	WVector3 getDestination();
	float getDistance();
	void setDestination(WVector3 w);
	void calculateDirectionFromDestination();
};

