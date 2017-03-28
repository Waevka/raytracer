#pragma once
#include "WCamera.h"
#include "WGeometricObject.h"
#include <list>
class WPerspectiveCamera :
	public WCamera
{
private:
	float d;
public:
	WPerspectiveCamera();
	~WPerspectiveCamera();
	void setDistance(float d);
	void generateRays(WRay** &rays, WViewPlane &viewPlane);
};

