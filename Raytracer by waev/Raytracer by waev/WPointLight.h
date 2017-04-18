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
	bool isInShadows(WRay &r, WShadingInfo &si);
	virtual bool castsShadows();
private:
	float ls;
	WVector3 location;
};

