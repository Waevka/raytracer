#pragma once
#include "WBRDF.h"
#include "WShadingInfo.h"

class WTransparentBDTF : public WBRDF
{
private:
	float ior;
	float kt;
public:
	WTransparentBDTF();
	~WTransparentBDTF();
	virtual bool tir(WShadingInfo & si);
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wt, const WVector3 &wo) const;
	virtual WColor rho(WShadingInfo &si, const WVector3 &wo) const;
	virtual WColor f(WShadingInfo &si, const WVector3 &wi, const WVector3 &wo) const;
	void setIor(float i);
	void setKt(float k);
	float getIor();
};

