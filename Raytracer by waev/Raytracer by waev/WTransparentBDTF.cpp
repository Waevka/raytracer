#include "WTransparentBDTF.h"
#include "WVector3.h"
#include "WShadingInfo.h"


WTransparentBDTF::WTransparentBDTF()
{
}


WTransparentBDTF::~WTransparentBDTF()
{
}

bool WTransparentBDTF::tir(WShadingInfo & si)
{
	WVector3 wo(-si.ray.direction);
	float cos_thetai = si.normal.dot(wo);
	float eta = ior;

	if (cos_thetai < 0.0) {
		eta = 1.0 / eta;
	}

	return (1.0 - (1.0f - cos_thetai * cos_thetai) / (eta * eta) < 1.0);
}

WColor WTransparentBDTF::sample_f(const WShadingInfo & si, WVector3 & wt, const WVector3 & wo) const
{
	WColor white(1.0f);
	WVector3 n(si.normal);
	float cos_thetai = n.dot(wo);
	float eta = ior;

	if (cos_thetai < 0.0) {
		cos_thetai = -cos_thetai;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - n * (cos_theta2 - cos_thetai / eta);

	return (white * kt / (eta*eta) / fabs(si.normal.dot(wt)));
}

WColor WTransparentBDTF::rho(WShadingInfo & si, const WVector3 & wo) const
{
	return WColor(); // ?
}

WColor WTransparentBDTF::f(WShadingInfo & si, const WVector3 & wi, const WVector3 & wo) const
{
	return WColor(); // ?
}

void WTransparentBDTF::setIor(float i)
{
	ior = i;
}

void WTransparentBDTF::setKt(float k)
{
	kt = k;
}
