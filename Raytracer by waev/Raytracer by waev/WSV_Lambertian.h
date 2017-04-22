#pragma once
#include "WBRDF.h"
#include "WTexture.h"
#define invPI 0.31830988618379067154
class WSV_Lambertian :
	public WBRDF
{
public:
	WSV_Lambertian();
	~WSV_Lambertian();
	void setKd(float f);
	float getKd();
	void setCd(WTexture *tex);
	WTexture* getCd();
	virtual WColor f(WShadingInfo &si, const WVector3 &wi, const WVector3 &wo) const;
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wi, const WVector3 &wo) const;
	virtual WColor rho(WShadingInfo &si, const WVector3 &wo) const;
private:
	float kd;
	WTexture *cd;

};

