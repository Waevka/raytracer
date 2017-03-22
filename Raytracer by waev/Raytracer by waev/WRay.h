#pragma once
#include "WVector3.h"

class WRay
{
private:
	WVector3 origin;
	WVector3 direction;
	WVector3 destination;
	float distance;
public:
	WRay();
	WRay(WVector3 o, WVector3 d);
	~WRay();
};

