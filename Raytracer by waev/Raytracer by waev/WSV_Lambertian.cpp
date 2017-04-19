#include "WSV_Lambertian.h"



WSV_Lambertian::WSV_Lambertian()
{
}


WSV_Lambertian::~WSV_Lambertian()
{
}

void WSV_Lambertian::setKd(float f)
{
	kd = f;
}

float WSV_Lambertian::getKd()
{
	return kd;
}

void WSV_Lambertian::setCd(WTexture * tex)
{
	cd = tex;
}

WTexture * WSV_Lambertian::getCd()
{
	return cd;
}

WColor WSV_Lambertian::f(const WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{
	return (cd->getColor(si) * kd * invPI);
}

WColor WSV_Lambertian::sample_f(const WShadingInfo & si, WVector3 & wi, const WVector3 & wo) const
{
	return WColor(); //?
}

WColor WSV_Lambertian::rho(const WShadingInfo & si, const WVector3 & wo) const
{
	return (cd->getColor(si) * kd);
}