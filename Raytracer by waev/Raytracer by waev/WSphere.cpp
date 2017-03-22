#include "WSphere.h"



WSphere::WSphere()
{
	origin = WVector3(0, 0, 0);
	radius = 1.0f;
}

WSphere::WSphere(WVector3 v, float r)
{
	origin = WVector3(v);
	radius = r;
}


WSphere::~WSphere()
{
}
