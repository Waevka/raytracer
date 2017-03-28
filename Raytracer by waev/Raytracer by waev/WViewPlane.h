#pragma once
#include "WRay.h"

class WViewPlane
{
private:
	float pixelSize;
	int width;
	int height;
public:
	WViewPlane(float ps, int w, int h);
	WViewPlane();
	~WViewPlane();
	void setPixelSize(float ps);
	void setWidth(int w);
	void setHeight(int h);
	float getPixelSize();
	int getWidth();
	int getHeight();
	WRay getRayAt(int x, int y);
};

