#include "WSphere.h"
#include <math.h>
#include <sstream>
#include <string>



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

std::string WSphere::toString()
{
	std::stringstream ss;
	ss << "WSphere [r: " << radius << ", origin: " << origin.toString() << "]";
	return ss.str();
}

// 0 - miss
// 1 - inprim
// 2 - hit
int WSphere::Intersect(WRay ray, float & dist)
{
	WVector3 v = ray.getOrigin() - origin;
	float b = -v.dot(ray.getDirection());
	float det = b*b - v.dot(v) + radius*radius;
	int returnValue = 0;
	//!
	dist = 2500.0f;

	if (det > 0) {
		det = sqrtf(det);
		float i1 = b - det;
		float i2 = b + det;

		if (i2 > 0) {
			if (i1 < 0) {
				if (i2 < dist) {
					dist = i2;
					returnValue = 1;
				}
			}
			else {
				if (i1 < dist) {
					dist = i1;
					returnValue = 2;
				}
			}
		}
	}
	else if (det == 0) {
		returnValue = 1;
		dist = b;
	}

	return returnValue;
}
