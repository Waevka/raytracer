#include "WViewPlane.h"



WViewPlane::WViewPlane(float ps, int w, int h)
{
	pixelSize = ps;
	width = w;
	height = h;
}

WViewPlane::WViewPlane()
{
	pixelSize = 0.5f;
	width = 10;
	height = 10;
}


WViewPlane::~WViewPlane()
{
}

void WViewPlane::setPixelSize(float ps)
{
	this->pixelSize = ps;
}

void WViewPlane::setWidth(int w)
{
	width = w;
}

void WViewPlane::setHeight(int h)
{
	height = h;
}

float WViewPlane::getPixelSize()
{
	return pixelSize;
}

int WViewPlane::getWidth()
{
	return width;
}

int WViewPlane::getHeight()
{
	return height;
}

WRay WViewPlane::getRayAt(int x, int y)
{
	return WRay();
}
