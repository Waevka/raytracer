#pragma once
#include "WCamera.h"
class WOrthoCamera :
	public WCamera
{
public:
	WOrthoCamera();
	~WOrthoCamera();
	void generateRays(WRay** &rays, WViewPlane &viewPlane);
};

