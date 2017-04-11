#include "WMatteMaterial.h"



WMatteMaterial::WMatteMaterial()
{
}


WMatteMaterial::~WMatteMaterial()
{
}

void WMatteMaterial::setKa(float k)
{
	ambient->setKd(k);
}

void WMatteMaterial::setKd(float k)
{
	diffuse->setKd(k);
}

void WMatteMaterial::setCd(WColor c)
{
	ambient->setCd(c);
	diffuse->setCd(c);
}
