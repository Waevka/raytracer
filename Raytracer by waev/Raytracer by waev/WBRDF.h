#pragma once
#include "WColor.h"
#include "WShadingInfo.h"
#include "WVector3.h"
#include "WCamera.h"
class WBRDF
{
public:
	WBRDF();
	~WBRDF();
	virtual WColor f(WShadingInfo &si, const WVector3 &wi, const WVector3 &wo) const = 0;
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wi, const WVector3 &wo) const = 0;
	virtual WColor rho(WShadingInfo &si, const WVector3 &wo) const = 0;
protected:
	WCamera* cameraSampler; //TODO: ???
};

