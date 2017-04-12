#include "WPointLight.h"



WPointLight::WPointLight()
{
}


WPointLight::~WPointLight()
{
}

WVector3 WPointLight::getDirection(WShadingInfo & si)
{
	return WVector3((location - si.hitPoint).hat());
}

WColor WPointLight::L(WShadingInfo & si)
{
	return color * ls;
}

void WPointLight::scaleRadiance(float f)
{
	ls = f;
}

void WPointLight::setLocation(WVector3 v)
{
	location = v;
}

bool WPointLight::isInShadows(WRay & r, WShadingInfo &si)
{
	float t;
	float d = location.distance(r.getOrigin());
	for (std::list<WGeometricObject*>::iterator iter = si.world.objects.begin(); iter != si.world.objects.end(); iter++) {
		if ((*iter)->shadowHit(r, t) && t < d) return true;
	}
	return false;
}

bool WPointLight::castsShadows()
{
	return true;
}
