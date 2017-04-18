#pragma once
#include "WVector3.h"
#include "WShadingInfo.h"
#include "WColor.h"
class WLight
{
public:
	WLight();
	~WLight();
	virtual WVector3 getDirection(WShadingInfo &si) = 0;
	virtual WColor L(WShadingInfo &si) = 0;
	virtual bool isInShadows(WRay & r, WShadingInfo &si) = 0;
	virtual bool castsShadows() = 0;
	virtual void setColor(WColor c);
protected:
	bool shadows;
	WColor color;
};

