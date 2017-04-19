#include "WSV_MatteMaterial.h"
#include "WWorld.h"


WSV_MatteMaterial::WSV_MatteMaterial() : WMaterial(), diffuse(new WSV_Lambertian), ambient(new WSV_Lambertian)
{
}


WSV_MatteMaterial::~WSV_MatteMaterial()
{
}

WColor WSV_MatteMaterial::shade(WShadingInfo & si)
{
	WVector3 wo = -si.ray.direction;
	WColor L = ambient->rho(si, wo) * si.world.ambient->L(si);

	for (int j = 0; j < si.world.lights.size(); j++) {
		WVector3 wi = si.world.lights[j]->getDirection(si);
		float ndotwi = (float)si.normal.dot(wi);

		if (ndotwi > 0.0) {
			bool isInShadow = false;

			if (si.world.lights[j]->castsShadows()) {
				WRay shadowRay(si.hitPoint, wi);
				isInShadow = si.world.lights[j]->isInShadows(shadowRay, si);
			}
			if (!isInShadow) {
				WColor diff = diffuse->f(si, wo, wi);
				WColor light = si.world.lights[j]->L(si);
				L = L + diff * light * ndotwi;
			}
		}
	}

	return L;
}

void WSV_MatteMaterial::setCd(WTexture * t_ptr)
{
	ambient->setCd(t_ptr);
	diffuse->setCd(t_ptr);
}

void WSV_MatteMaterial::setKa(float k)
{
	ambient->setKd(k);
}

void WSV_MatteMaterial::setKd(float k)
{
	diffuse->setKd(k);
}