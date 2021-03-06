#include "WMatteMaterial.h"
#include "WWorld.h"


WMatteMaterial::WMatteMaterial() : WMaterial(), ambient(new WLambertian), diffuse(new WLambertian)
{
}

WMatteMaterial::WMatteMaterial(const WMatteMaterial & m) : WMaterial()
{
	ambient = m.ambient;
	diffuse = m.diffuse;
	//may need a fix;
}


WMatteMaterial::~WMatteMaterial()
{
}

WColor WMatteMaterial::shade(WShadingInfo & si)
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

WColor WMatteMaterial::getCd() {
	return diffuse->getCd();
}
