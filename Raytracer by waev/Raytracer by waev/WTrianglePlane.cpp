#include "WTrianglePlane.h"
#include "WTriangle.h"


WTrianglePlane::WTrianglePlane(WVector3 & center, float width, float height) : WModel(), center(center), width(width), height(height)
{
	WTriangle *first = new WTriangle(
		WVector3(center.x, center.y - 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(1.0f, 0.0f, 0.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x, center.y + 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(1.0f, 0.0f, 0.0f)
	);
	addObject(first);
	addObject(second);
}

WTrianglePlane::~WTrianglePlane()
{
}
