#pragma once
#include "WCamera.h"
#include "WGeometricObject.h"
#include <list>
class WPerspectiveCamera :
	public WCamera
{
private:
	float d;
	int viewPlaneWidth;
	int viewPlaneHeight;
	float pixelSize;
public:
	WPerspectiveCamera(WWorld &wr);
	~WPerspectiveCamera();
	void setDistance(float d);
	void generateRays(WRay** &rays, WViewPlane &viewPlane);
	WRay generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j);
	WRay generateSinglePathBounceRay(WRay &ray, float xOffset, float yOffset, int i, int j, WVector3 hitPoint);
};

