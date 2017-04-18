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
	float t = 400.0f;
	float d = location.distance(r.origin);
	WWorld &w = si.world;
	for (int j = 0; j < w.objects.size();j++) {
		if (w.objects[j]->shadowHit(r, t) && t < d) return true;
	}
	return false;
}

bool WPointLight::castsShadows()
{
	return true;
}
