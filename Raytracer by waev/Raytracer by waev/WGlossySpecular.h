#pragma once
#include "WBRDF.h"
#define invPI 0.31830988618379067154
class WGlossySpecular :
	public WBRDF
{
public:
	WGlossySpecular();
	~WGlossySpecular();
	void setKs(float k);
	float getKs();
	void setCs(WColor c);
	WColor getCs();
	void setExp(float e);
	float getExp();

	virtual WColor f(const WShadingInfo &si, const WVector3 &wi, const WVector3 &wo) const;
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wi, const WVector3 &wo) const;
	virtual WColor rho(const WShadingInfo &si, const WVector3 &wo) const;

private:
	float ks;
	WColor cs;
	float exp;
	//WSampler *sampler;
};

