#include "WTransparentMaterial.h"
#include "WShadingInfo.h"
#include "WCamera.h"
#include "WWorld.h"

WTransparentMaterial::WTransparentMaterial() : WPhong(), transparent(new WTransparentBDTF), mirror(new WMirrorBRDF)
{
}


WTransparentMaterial::~WTransparentMaterial()
{
}

void WTransparentMaterial::setKr(float f)
{
	mirror->setKr(f);
}

void WTransparentMaterial::setIor(float i)
{
	transparent->setIor(i);
}

void WTransparentMaterial::setKt(float k)
{
	transparent->setKt(k);
}

WColor WTransparentMaterial::shade(WShadingInfo &si)
{
	WColor L(WPhong::shade(si));
	WVector3 wo = -si.ray.direction;
	WVector3 wi;
	WColor fr = transparent->sample_f(si, wi, wo);
	WRay reflectedRay(si.hitPoint, wi);

	if (transparent->tir(si)) {
		WColor transparentColor = si.world.perspCam->intersectSingleReflectionRay(reflectedRay,
			si, 0, 0, si.world.perspCam->aliasingLevel + 1);
		L = L + transparentColor;
		// kr = 1.0;
	}
	else {
		WVector3 wt;
		WColor ft = transparent->sample_f(si, wt, wi);
		WRay transmittedRay(si.hitPoint, wt);

		L = L + si.world.perspCam->intersectSingleReflectionRay(reflectedRay,
			si, 0, 0, si.world.perspCam->aliasingLevel + 1) * fabs(si.normal.dot(wi));

		L = L + si.world.perspCam->intersectSingleReflectionRay(transmittedRay,
			si, 0, 0, si.world.perspCam->aliasingLevel + 1) * fabs(si.normal.dot(wt));
	}

	return L;
}
