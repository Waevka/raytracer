#pragma once
#include "WTexture.h"
#include "WImage.h"
class WImageTexture :
	public WTexture
{
public:
	WImageTexture();
	~WImageTexture();

	virtual WColor getColor(const WShadingInfo &si) const;
private:
	int hres;
	int vres;
	WImage  *image_ptr;
	WMapping *mapping_ptr;
};

