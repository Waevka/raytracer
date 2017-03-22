#include "WRay.h"



WRay::WRay()
{
	origin = WVector3(0, 0, 0);
	direction = WVector3(0, 0, 0);
	distance = 0.0f;
}

WRay::WRay(WVector3 o, WVector3 d)
{
	origin = WVector3(o);
	destination = WVector3(d);
}


WRay::~WRay()
{
}
