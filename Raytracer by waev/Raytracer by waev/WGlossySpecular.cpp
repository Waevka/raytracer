#include "WGlossySpecular.h"



WColor WGlossySpecular::f(const WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{	
	WColor c(0.0, 0.0, 0.0);
	float ndotwi = (float)si.normal.dot(wi);
	WVector3 r(-wi + si.normal * 2.0 * ndotwi);
	float rdotwo = (float)r.dot(wo);

	if (rdotwo > 0.0) {
		c = ks * pow(rdotwo, exp);
	}

	return c;
}

WColor WGlossySpecular::sample_f(const WShadingInfo & si, WVector3 & wi, const WVector3 & wo) const
{
	return WColor();
}

WColor WGlossySpecular::rho(const WShadingInfo & si, const WVector3 & wo) const
{
	return WColor(0.0, 0.0, 0.0);
}

WGlossySpecular::WGlossySpecular()
{
}


WGlossySpecular::~WGlossySpecular()
{
}

void WGlossySpecular::setKs(float k)
{
	ks = k;
}

float WGlossySpecular::getKs()
{
	return ks;
}

void WGlossySpecular::setCs(WColor c)
{
	cs = c;
}

WColor WGlossySpecular::getCs()
{
	return cs;
}

void WGlossySpecular::setExp(float e)
{
	exp = e;
}

float WGlossySpecular::getExp()
{
	return exp;
}
