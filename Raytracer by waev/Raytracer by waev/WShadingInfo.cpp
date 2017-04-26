#include "WShadingInfo.h"



WShadingInfo::WShadingInfo(WWorld &wr) : hitObject(false), material(NULL), hitPoint(),
localHitPoint(), normal(), ray(), depth(0), direction(), world(wr), name("none"), u(0.0f), v(0.0f),
rayBounces(0)
{
}


WShadingInfo::~WShadingInfo()
{
}

//WShadingInfo::WShadingInfo() : hitObject(false),
//material(NULL), hitPoint(), localHitPoint(), normal(), ray(), depth(0), direction()/*, w(w)*/
//{
//}

WShadingInfo::WShadingInfo(const WShadingInfo & si) :
	hitObject(si.hitObject), material(si.material), hitPoint(si.hitPoint),
	localHitPoint(si.localHitPoint), normal(si.normal), ray(si.ray),
	depth(si.depth), direction(si.direction), world(si.world), name("none"), u(si.u), v(si.v),
	rayBounces(si.rayBounces)
{
}
