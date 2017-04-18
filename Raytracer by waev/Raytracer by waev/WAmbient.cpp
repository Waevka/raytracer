#include "WAmbient.h"



WAmbient::WAmbient() : WLight(), ls(1.0f)
{
}


WAmbient::~WAmbient()
{
}

WVector3 WAmbient::getDirection(WShadingInfo & si)
{	
	WVector3 v(0.0);
	return v;
}

WColor WAmbient::L(WShadingInfo & si)
{
	return color * ls;
}

bool WAmbient::isInShadows(WRay & r, WShadingInfo & si)
{
	return false;
}

bool WAmbient::castsShadows()
{
	return true;
}
