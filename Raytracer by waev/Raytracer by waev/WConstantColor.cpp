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

WColor WConstantColor::getColor(const WShadingInfo & si) const
{
	return color;
}
