#pragma once
#include "WCamera.h"
class WOrthoCamera :
	public WCamera
{
public:
	WOrthoCamera(WWorld &wr);
	~WOrthoCamera();
	void generateRays(WRay** &rays, WViewPlane &viewPlane);
	WRay generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j);
};

