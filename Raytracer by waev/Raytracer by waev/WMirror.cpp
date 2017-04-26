#include "WMirror.h"
#include "WWorld.h"


WMirror::WMirror()
{
}


WMirror::~WMirror()
{
}

WColor WMirror::shade(WShadingInfo & si)
{
	WVector3 wo = -si.ray.direction;
	WVector3 wi;
	WColor fr = 
	WColor L = ambient->rho(si, wo) * si.world.ambient->L(si);
	int numLights = si.world.lights.size();

	for (int j = 0; j < numLights; j++) {
		WVector3 wi = si.world.lights[j]->getDirection(si);
		float ndotwi = (float)si.normal.dot(wi);

		if (ndotwi > 0.0) {
			bool isInShadow = false;

			if (si.world.lights[j]->castsShadows()) {
				WRay shadowRay(si.hitPoint, wi);
				isInShadow = si.world.lights[j]->isInShadows(shadowRay, si);
			}
			if (!isInShadow) {
				L = L + (diffuse->f(si, wo, wi) + specular->f(si, wo, wi)) *
					si.world.lights[j]->L(si) * ndotwi;
			}


		}
	}

	return L;
}
