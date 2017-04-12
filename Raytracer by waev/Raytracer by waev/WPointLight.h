#pragma once
#include "WLight.h"
#include <list>
#include "WVector3.h"
#include "WColor.h"
#include "WGeometricObject.h"
#include "WWorld.h"
class WPointLight :
	public WLight
{
public:
	WPointLight();
	~WPointLight();
	virtual WVector3 getDirection(WShadingInfo &si);
	virtual WColor L(WShadingInfo &si);
	virtual void scaleRadiance(float f);
	virtual void setLocation(WVector3 v);
	bool isInShadow(WRay &r, WShadingInfo &si);
private:
	float ls;
	WColor color;
	WVector3 location;
};

