#pragma once
#include "WTexture.h"
#include "WImage.h"
#include "WMapping.h"
class WImageTexture :
	public WTexture
{
public:
	WImageTexture();
	~WImageTexture();

	void setColor(WImage *c);
	virtual WColor getColor(WShadingInfo &si) const;
private:
	int hres;
	int vres;
	WImage  *image_ptr;
	WMapping *mapping_ptr;
};

