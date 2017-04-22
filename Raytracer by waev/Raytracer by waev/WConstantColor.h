#pragma once
#include "WTexture.h"
#include "WColor.h"
#include "WShadingInfo.h"
class WConstantColor :
	public WTexture
{
public:
	WConstantColor();
	~WConstantColor();
	void setColor(const WColor c);
	virtual WColor getColor(WShadingInfo &si) const;
private:
	WColor color;
};

