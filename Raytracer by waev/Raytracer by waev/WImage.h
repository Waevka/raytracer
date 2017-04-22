#pragma once
#include "WColor.h"
class WImage
{
private:
	WColor ***image;
	int width;
	int height;
public:
	WImage(int width, int height);
	WImage();
	~WImage();
	void setPixel(WColor &c, int x, int y);
	WColor getPixel(int x, int y);
	int getWidth();
	int getHeight();
};

