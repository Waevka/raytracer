#pragma once
#include "WVector3.h"
#include "WColor.h"
#include "WRay.h"
#include "WMaterial.h"
class WShadingInfo
{
public:
	WShadingInfo();
	~WShadingInfo();

	bool hitObject;
	WMaterial *material;
	WVector3 hitPoint;
	WVector3 localHitPoint;
	WVector3 normal;
	WColor color;
	WRay ray;
	int depth;
	WVector3 direction;
	//WWorld world;

	WShadingInfo(const WShadingInfo &si);

};

