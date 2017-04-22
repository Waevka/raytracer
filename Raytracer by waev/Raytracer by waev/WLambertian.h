#pragma once
#include "WBRDF.h"
#include "WColor.h"
#include "WVector3.h"
#define invPI 0.31830988618379067154
class WLambertian : public WBRDF
{
private:
	float kd;
	WColor cd; // diffuse color
public:
	WLambertian();
	~WLambertian();
	void setKd(float f);
	float getKd();
	void setCd(WColor c);
	WColor getCd();

	virtual WColor f(WShadingInfo &si, const WVector3 &wi, const WVector3 &wo) const;
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wi, const WVector3 &wo) const;
	virtual WColor rho(WShadingInfo &si, const WVector3 &wo) const;
};

