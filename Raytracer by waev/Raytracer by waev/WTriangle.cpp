#include "WTriangle.h"



WTriangle::WTriangle() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	v0 = WVector3(1, 0, 0);
	v1 = WVector3(0, 1, 0);
	v2 = WVector3(0, 0, 1);
	normal = WVector3(0, 1, 0);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2) : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WColor c) : WGeometricObject(c)
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
}


WTriangle::~WTriangle()
{
}

int WTriangle::Intersection(WRay ray, float & dist)
{
	return 0;
}
