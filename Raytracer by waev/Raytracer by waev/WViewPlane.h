#pragma once
#include "WRay.h"

class WViewPlane
{
private:
	float pixelSize;
	int width;
	int height;
	WRay ray;
public:
	WViewPlane(float ps, int w, int h, WRay r);
	WViewPlane();
	~WViewPlane();
	void setPixelSize(float ps);
	void setWidth(int w);
	void setHeight(int h);
	float getPixelSize();
	int getWidth();
	int getHeight();
	WRay getRayAt(int x, int y);
	WRay getRay();
};

