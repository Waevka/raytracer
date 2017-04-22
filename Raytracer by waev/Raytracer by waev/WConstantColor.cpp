#include "WConstantColor.h"



WConstantColor::WConstantColor()
{
}


WConstantColor::~WConstantColor()
{
}

void WConstantColor::setColor(const WColor c)
{
	color = c;
}

WColor WConstantColor::getColor(WShadingInfo & si) const
{
	return color;
}
