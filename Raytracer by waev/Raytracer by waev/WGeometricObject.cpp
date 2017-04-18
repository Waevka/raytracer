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

void WGeometricObject::minXYZ(float & mx, float & my, float & mz)
{
	mx = 0;
	my = 0;
	mz = 0;
}

void WGeometricObject::maxXYZ(float & mx, float & my, float & mz)
{
	mx = 0;
	my = 0;
	mz = 0;
}
