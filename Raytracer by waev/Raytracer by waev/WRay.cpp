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
	direction = WVector3(d);
}


WRay::~WRay()
{
}

WVector3 WRay::getOrigin()
{
	return origin;
}

WVector3 WRay::getDirection()
{
	return direction;
}

WVector3 WRay::getDestination()
{
	return destination;
}

float WRay::getDistance()
{
	return distance;
}

void WRay::setDestination(WVector3 w)
{
	this->destination = w;
}

void WRay::calculateDirectionFromDestination()
{

	direction.normalize();
}
