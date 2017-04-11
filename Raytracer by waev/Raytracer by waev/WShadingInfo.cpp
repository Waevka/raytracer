#include "WShadingInfo.h"



WShadingInfo::WShadingInfo()
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
	depth(si.depth), direction(si.direction)
{
}
