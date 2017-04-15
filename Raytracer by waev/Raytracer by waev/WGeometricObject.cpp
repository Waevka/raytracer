#include "WGeometricObject.h"


WGeometricObject::WGeometricObject()
{
}

WGeometricObject::WGeometricObject(WColor c)
{
	this->color = c;
	this->material = new WMaterial();
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
	return material;
}

void WGeometricObject::setMaterial(WMaterial *m)
{
	material = m;
}

int WGeometricObject::Intersection(WRay &ray, float & dist, WShadingInfo &ws)
{
	return 0;
}

bool WGeometricObject::shadowHit(WRay & r, float & tmin)
{
	return false;
}
