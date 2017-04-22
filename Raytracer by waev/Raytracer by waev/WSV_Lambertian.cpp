#include "WSV_Lambertian.h"



WSV_Lambertian::WSV_Lambertian() : cd(NULL)
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

WColor WSV_Lambertian::f(WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{	
	if (cd == NULL) {
		return (WColor(1.0, 0.0, 0.7) * kd * invPI);
	}
	return (cd->getColor(si) * kd * invPI);
}

WColor WSV_Lambertian::sample_f(const WShadingInfo & si, WVector3 & wi, const WVector3 & wo) const
{
	return WColor(); //?
}

WColor WSV_Lambertian::rho(WShadingInfo & si, const WVector3 & wo) const
{	
	if (cd == NULL) {
		return (WColor(1.0, 0.0, 0.7) * kd);
	}
	return (cd->getColor(si) * kd);
}
