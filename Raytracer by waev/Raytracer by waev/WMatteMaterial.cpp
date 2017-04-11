#include "WMatteMaterial.h"



WMatteMaterial::WMatteMaterial() : WMaterial(), ambient(new WLambertian), diffuse(new WLambertian)
{
}


WMatteMaterial::~WMatteMaterial()
{
}

WColor WMatteMaterial::shade(WShadingInfo & si)
{
	WVector3 wo = -si.ray.getDirection();
	return WColor();
	//WColor L = ambient->rho(si, wo) * si.
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
