#include "WRectangleMap.h"
#include <math.h>


WRectangleMap::WRectangleMap()
{
}


WRectangleMap::~WRectangleMap()
{
}

void WRectangleMap::getTexelCoordinates(WVector3 & localHitPoint, int hres, int vres, int & row, int & column)
{
	WVector3 lhp(localHitPoint);

	float v = lhp.y;
	float u = lhp.z;

	column = (int)((hres - 1)  * u);
	row = (int)((vres - 1) * v);
}
