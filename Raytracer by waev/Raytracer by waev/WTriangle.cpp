#include "WTriangle.h"



WTriangle::WTriangle() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	v0 = WVector3(1, 0, 0);
	v1 = WVector3(0, 1, 0);
	v2 = WVector3(0, 0, 1);
	normal = WVector3(0, 1, 0);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2) : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WVector3 n) : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
	this->normal = WVector3(n.x, n.y, n.z);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WColor c) : WGeometricObject(c)
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WVector3 n, WColor c) : WGeometricObject(c)
{
	this->v0 = WVector3(v0.getX(), v0.getY(), v0.getZ());
	this->v1 = WVector3(v1.getX(), v1.getY(), v1.getZ());
	this->v2 = WVector3(v2.getX(), v2.getY(), v2.getZ());
	this->normal = WVector3(n.x, n.y, n.z);
}


WTriangle::~WTriangle()
{
}

int WTriangle::Intersection(WRay ray, float & dist, WShadingInfo &ws)
{
	int hit = 2;

	double	a = v0.x - v1.x,
		b = v0.x - v2.x,
		c = ray.getDirection().x,
		d = v0.x - ray.getOrigin().x;
	double e = v0.y - v1.y,
		f = v0.y - v2.y,
		g = ray.getDirection().y,
		h = v0.y - ray.getOrigin().y;
	double i = v0.z - v1.z,
		j = v0.z - v2.z,
		k = ray.getDirection().z,
		l = v0.z - ray.getOrigin().z;

	double m = f*k - g*j,
		n = h*k - g*l,
		p = f*l - h*j;
	double q = g*i - e*k,
		s = e*j - f*i;

	double inv_denom = 1.0 / (a*m + b*q + c*s);

	double e1 = d*m - b*n - c*p;
	double beta = e1 * inv_denom;

	if (beta < 0.0) {
		hit = 0;
		return hit;
	}

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0) {
		hit = 0;
		return hit;
	}

	if (beta + gamma > 1.0) {
		hit = 0;
		return hit;
	}

	double e3 = a*p - b*r + d*s;
	double t = e3 * inv_denom;

	if (t < 0.000001) {
		hit = 0;
		return hit;
	}

	dist = t;
	ws.normal = normal;
	ws.localHitPoint = ray.getOrigin() + ray.getDirection() * t;

	return hit;
}

bool WTriangle::shadowHit(WRay & ray, float & tmin)
{
	bool hit = true;

	double	a = v0.x - v1.x,
		b = v0.x - v2.x,
		c = ray.getDirection().x,
		d = v0.x - ray.getOrigin().x;
	double e = v0.y - v1.y,
		f = v0.y - v2.y,
		g = ray.getDirection().y,
		h = v0.y - ray.getOrigin().y;
	double i = v0.z - v1.z,
		j = v0.z - v2.z,
		k = ray.getDirection().z,
		l = v0.z - ray.getOrigin().z;

	double m = f*k - g*j,
		n = h*k - g*l,
		p = f*l - h*j;
	double q = g*i - e*k,
		s = e*j - f*i;

	double inv_denom = 1.0 / (a*m + b*q + c*s);

	double e1 = d*m - b*n - c*p;
	double beta = e1 * inv_denom;

	if (beta < 0.0) {
		hit = false;
		return hit;
	}

	double r = e*l - h*i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0) {
		hit = false;
		return hit;
	}

	if (beta + gamma > 1.0) {
		hit = false;
		return hit;
	}

	double e3 = a*p - b*r + d*s;
	double t = e3 * inv_denom;

	if (t < 0.00001) {
		hit = false;
		return hit;
	}

	tmin = t;

	return hit;
}
