#include "WMirror.h"
#include "WWorld.h"
#include "WShadingInfo.h"
#include "WCamera.h"


WMirror::WMirror() : WPhong(), mirror(new WMirrorBRDF)
{
}


WMirror::~WMirror()
{
}

WColor WMirror::shade(WShadingInfo & si)
{	
	if (si.rayBounces > 5) {
		return WColor(0.2f);
	}
	WColor L(WPhong::shade(si));
	WVector3 wo = -si.ray.direction;
	WVector3 wi;
	WColor fr = mirror->sample_f(si, wi, wo);
	WRay reflectedRay(si.hitPoint, wi);

	WColor reflectedColor = si.world.perspCam->intersectSingleReflectionRay(reflectedRay,
		si, 0, 0, si.world.perspCam->aliasingLevel + 1);
	L = fr * reflectedColor * si.normal.dot(wi);

	return L;
}

void WMirror::setKr(float f)
{
	mirror->setKr(f);
}

void WMirror::setCr(WColor c)
{
	mirror->setCr(c);
}
