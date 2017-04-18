#include "WPhong.h"
#include "WWorld.h"
#include "WLambertian.h"



WPhong::WPhong() : WMaterial(), ambient(new WLambertian), diffuse(new WLambertian), specular(new WGlossySpecular)
{
}


WPhong::~WPhong()
{
}

WColor WPhong::shade(WShadingInfo & si)
{
	WVector3 wo = -si.ray.direction;
	WColor L = ambient->rho(si, wo) * si.world.ambient->L(si);
	int numLights = si.world.lights.size();

	for (int j = 0; j < numLights; j++) {
		WVector3 wi = si.world.lights[j]->getDirection(si);
		float ndotwi = (float)si.normal.dot(wi);
	
		if (ndotwi > 0.0) {
			L = L + (diffuse->f(si, wo, wi) + specular->f(si, wo, wi)) * 
				si.world.lights[j]->L(si) * ndotwi;
		}
	}

	return L;
}

void WPhong::setKa(float k)
{
	ambient->setKd(k);
}

void WPhong::setKd(float k)
{
	diffuse->setKd(k);
}

void WPhong::setKs(float k)
{
	specular->setKs(k);
}

void WPhong::setCd(WColor c)
{
	ambient->setCd(c);
	diffuse->setCd(c);
	specular->setCs(c);
}

void WPhong::setExp(float f)
{
	specular->setExp(f);
}
