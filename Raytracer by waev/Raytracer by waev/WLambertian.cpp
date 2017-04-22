#include "WLambertian.h"



WLambertian::WLambertian()
{
	cd = WColor();
	kd = 0.0f;
}


WLambertian::~WLambertian()
{
}

void WLambertian::setKd(float f)
{
	kd = f;
}

float WLambertian::getKd()
{
	return kd;
}

void WLambertian::setCd(WColor c)
{
	cd = c;
}

WColor WLambertian::getCd()
{
	return cd;
}

WColor WLambertian::f(WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{
	WColor wc(cd);
	wc = wc * kd;
	wc = wc * invPI;
	return (wc);
}

WColor WLambertian::sample_f(const WShadingInfo & si, WVector3 & wi, const WVector3 & wo) const
{
	return WColor(); ///////////////////////// careful
}

WColor WLambertian::rho(WShadingInfo & si, const WVector3 & wo) const
{
	WColor wc(cd);
	wc = wc * kd;
	return wc;
}
