#pragma once
#include "WLight.h"
#include "WVector3.h"
#include "WColor.h"
class WPointLight :
	public WLight
{
public:
	WPointLight();
	~WPointLight();
	virtual WVector3 getDirection(WShadingInfo &si);
	virtual WColor L(WShadingInfo &si);
private:
	float ls;
	WColor color;
	WVector3 location;
};

