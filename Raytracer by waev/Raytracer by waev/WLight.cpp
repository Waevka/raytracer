#include "WLight.h"



WLight::WLight() : color(1.0)
{
}


WLight::~WLight()
{
}

void WLight::setColor(WColor c)
{
	color = c;
}
