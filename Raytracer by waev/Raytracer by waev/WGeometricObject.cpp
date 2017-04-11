#include "WGeometricObject.h"



WGeometricObject::WGeometricObject(WColor c)
{
	this->color = c;
}


WGeometricObject::~WGeometricObject()
{
}

WColor WGeometricObject::getColor()
{
	return color;
}

WMaterial* WGeometricObject::getMaterial()
{
	return &material;
}

int WGeometricObject::Intersection(WRay ray, float & dist)
{
	return 0;
}
