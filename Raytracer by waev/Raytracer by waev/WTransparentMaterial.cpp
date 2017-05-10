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
	WVector3 wo = si.ray.direction;
	WVector3 wi;
	WColor fr = transparent->sample_f(si, wi, wo);
	WVector3 origin = si.hitPoint;
	origin = origin + (-si.normal) * 0.00001f;
	WRay reflectedRay(origin, wi);

		WColor transparentColor = si.world.perspCam->intersectSingleReflectionRay(reflectedRay,
			si, 0, 0, si.world.perspCam->aliasingLevel + 1);
		L = L*0.25 + transparentColor;

	return L;
}
