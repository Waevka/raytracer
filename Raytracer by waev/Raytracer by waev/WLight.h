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
protected:
	bool shadows;
};

