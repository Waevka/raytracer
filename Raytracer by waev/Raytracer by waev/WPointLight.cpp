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
