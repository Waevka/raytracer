#pragma once
#include "WLight.h"
#include "WVector3.h"
#include "WColor.h"

class WAmbient :
	public WLight
{
public:
	WAmbient();
	~WAmbient();
	virtual WVector3 getDirection(WShadingInfo &si);
	virtual WColor L(WShadingInfo &si);
private:
	float ls;
	WColor color;
};

