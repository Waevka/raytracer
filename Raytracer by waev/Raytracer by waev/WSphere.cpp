#include "WSphere.h"
#include <math.h>
#include <sstream>
#include <string>



WSphere::WSphere() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	origin = WVector3(0, 0, 0);
	radius = 1.0f;
}

WSphere::WSphere(WVector3 v, float r, WColor c) : WGeometricObject(c)
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
int WSphere::Intersection(WRay ray, float & dist, WShadingInfo &ws)
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
					ws.normal = (v + ray.getDirection() * dist) / radius;
					ws.localHitPoint = ray.getOrigin() + ray.getDirection() * dist;
					returnValue = 1;
				}
			}
			else {
				if (i1 < dist) {
					dist = i1;
					ws.normal = (v + ray.getDirection() * dist) / radius;
					ws.localHitPoint = ray.getOrigin() + ray.getDirection() * dist;
					returnValue = 2;
				}
			}
		}
	}
	else if (det == 0) {
		returnValue = 1;
		dist = b;
		ws.normal = (v + ray.getDirection() * dist) / radius;
		ws.localHitPoint = ray.getOrigin() + ray.getDirection() * dist;
	}

	return returnValue;
}

bool WSphere::shadowHit(WRay & r, float & tmin)
{
	WVector3 v = r.getOrigin() - origin;
	float b = -v.dot(r.getDirection());
	float det = b*b - v.dot(v) + radius*radius;
	int returnValue = 0;
	//!
	tmin = 2500.0f;

	if (det > 0.000001) {
		det = sqrtf(det);
		float i1 = b - det;
		float i2 = b + det;

		if (i2 > 0.000001) {
			if (i1 < 0.000001) {
				if (i2 < tmin) {
					tmin = i2;
					returnValue = 1;
				}
			}
			else {
				if (i1 < tmin) {
					tmin = i1;
					returnValue = 2;
				}
			}
		}
	}
	else if (det == 0) {
		returnValue = 1;
		tmin = b;
	}

	return returnValue;
}
