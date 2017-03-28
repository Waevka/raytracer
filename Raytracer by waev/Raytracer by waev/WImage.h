#pragma once
#include "WColor.h"
class WImage
{
private:
	WColor ***image;
public:
	WImage(int width, int height);
	~WImage();
	void setPixel(WColor &c, int x, int y);
	WColor getPixel(int x, int y);
};

