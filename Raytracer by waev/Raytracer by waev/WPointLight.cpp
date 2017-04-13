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
	WWorld &w = si.world;
	int objCount = (int)si.world.objects.size();
	for (int j = 0; j < objCount;j++) {
		if (w.objects[j]->shadowHit(r, t) && t < d) return true;
	}
	return false;
}

bool WPointLight::castsShadows()
{
	return true;
}
