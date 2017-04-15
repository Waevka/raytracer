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
int WSphere::Intersection(WRay &ray, float & dist, WShadingInfo &ws)
{
	WVector3 v = ray.origin - origin;
	float b = -v.dot(ray.direction);
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
					ws.normal = (v + ray.direction * dist) / radius;
					ws.localHitPoint = ray.origin + ray.direction * dist;
					returnValue = 1;
				}
			}
			else {
				if (i1 < dist) {
					dist = i1;
					ws.normal = (v + ray.direction * dist) / radius;
					ws.localHitPoint = ray.origin + ray.direction * dist;
					returnValue = 2;
				}
			}
		}
	}
	else if (det == 0) {
		returnValue = 1;
		dist = b;
		ws.normal = (v + ray.direction * dist) / radius;
		ws.localHitPoint = ray.origin + ray.direction * dist;
	}

	return returnValue;
}

bool WSphere::shadowHit(WRay & r, float & tmin)
{
	WVector3 v = r.origin - origin;
	float b = -v.dot(r.direction);
	float det = b*b - v.dot(v) + radius*radius;
	//!
	tmin = 2500.0f;

	if (det > 0.000001) {
		det = sqrtf(det);
		float i1 = b - det;
		float i2 = b + det;

		if (i2 > 0) {
			if (i1 < 0) {
				if (i2 < tmin) {
					tmin = i2;
					return false;
				}
			}
			else {
				if (i1 < tmin) {
					tmin = i1;
					return true;
				}
			}
		}
	}
	else {
		return false;
		tmin = b;
	}
	return false;
}

void WSphere::minXYZ(float & mx, float & my, float & mz)
{
	mx = origin.x - radius;
	my = origin.y - radius;
	mz = origin.z - radius;
}

void WSphere::maxXYZ(float & mx, float & my, float & mz)
{
	mx = origin.x + radius;
	my = origin.y + radius;
	mz = origin.z + radius;
}
