#include "WMirrorBRDF.h"



WMirrorBRDF::WMirrorBRDF()
{
}


WMirrorBRDF::~WMirrorBRDF()
{
}

void WMirrorBRDF::setKr(float k)
{
	kr = k;
}

float WMirrorBRDF::getKr()
{
	return kr;
}

void WMirrorBRDF::setCr(WColor c)
{
	cr = c;
}

WColor WMirrorBRDF::getCr()
{
	return cr;
}

WColor WMirrorBRDF::f(WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{
	return WColor(0.0f);
}

WColor WMirrorBRDF::sample_f(const WShadingInfo & si, WVector3 & wi, const WVector3 & wo) const
{
	float ndotwo = si.normal.dot(wo);
	wi = -wo + si.normal * ndotwo * 2.0;
	return (cr * kr / (si.normal.dot(wi)));
	// WColor();
}

WColor WMirrorBRDF::rho(WShadingInfo & si, const WVector3 & wo) const
{
	return WColor(0.0f);
}
