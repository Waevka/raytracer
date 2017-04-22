#pragma once
#include "WShadingInfo.h"
#include "WColor.h"
class WTexture
{
public:
	WTexture();
	~WTexture();
	virtual WColor getColor(WShadingInfo &si) const = 0;
};

