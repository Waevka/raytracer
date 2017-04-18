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
	this->v0 = WVector3(v0.x, v0.y, v0.z);
	this->v1 = WVector3(v1.x, v1.y, v1.z);
	this->v2 = WVector3(v2.x, v2.y, v2.z);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WVector3 n) : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
	this->v0 = WVector3(v0.x, v0.y, v0.z);
	this->v1 = WVector3(v1.x, v1.y, v1.z);
	this->v2 = WVector3(v2.x, v2.y, v2.z);
	this->normal = WVector3(n.x, n.y, n.z);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WColor c) : WGeometricObject(c)
{
	this->v0 = WVector3(v0.x, v0.y, v0.z);
	this->v1 = WVector3(v1.x, v1.y, v1.z);
	this->v2 = WVector3(v2.x, v2.y, v2.z);
}

WTriangle::WTriangle(WVector3 v0, WVector3 v1, WVector3 v2, WVector3 n, WColor c) : WGeometricObject(c)
{
	this->v0 = WVector3(v0.x, v0.y, v0.z);
	this->v1 = WVector3(v1.x, v1.y, v1.z);
	this->v2 = WVector3(v2.x, v2.y, v2.z);
	this->normal = WVector3(n.x, n.y, n.z);
}


WTriangle::~WTriangle()
{
}

int WTriangle::Intersection(WRay &ray, float & dist, WShadingInfo &ws)
{	
	int hit = 2;

	double	a = v0.x - v1.x,
		b = v0.x - v2.x,
		c = ray.direction.x,
		d = v0.x - ray.origin.x;
	double e = v0.y - v1.y,
		f = v0.y - v2.y,
		g = ray.direction.y,
		h = v0.y - ray.origin.y;
	double i = v0.z - v1.z,
		j = v0.z - v2.z,
		k = ray.direction.z,
		l = v0.z - ray.origin.z;

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

	if (t < 0.00001) {
		hit = 0;
		return hit;
	}

	ws.normal = normal;
	ws.localHitPoint = ray.origin + ray.direction * (float)t;
	dist = (float)t;
	return hit;
}

bool WTriangle::shadowHit(WRay & ray, float & tmin)
{
	bool hit = true;

	double	a = v0.x - v1.x,
		b = v0.x - v2.x,
		c = ray.direction.x,
		d = v0.x - ray.origin.x;
	double e = v0.y - v1.y,
		f = v0.y - v2.y,
		g = ray.direction.y,
		h = v0.y - ray.origin.y;
	double i = v0.z - v1.z,
		j = v0.z - v2.z,
		k = ray.direction.z,
		l = v0.z - ray.origin.z;

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

	if (t < 0.001) {
		hit = false;
		return hit;
	}

	tmin = (float)t;

	return hit;
}

void WTriangle::minXYZ(float & mx, float & my, float & mz)
{
	mx = v0.x;
	if (mx > v1.x)
		mx = v1.x;
	if (mx > v2.x)
		mx = v2.x;

	my = v0.y;
	if (my > v1.y)
		my = v1.y;
	if (my > v2.y)
		my = v2.y;

	mz = v0.z;
	if (mz > v1.z)
		mz = v1.z;
	if (mz > v2.z)
		mz = v2.z;
}

void WTriangle::maxXYZ(float & mx, float & my, float & mz)
{
	mx = v0.x;
	if (mx < v1.x)
		mx = v1.x;
	if (mx < v2.x)
		mx = v2.x;

	my = v0.y;
	if (my < v1.y)
		my = v1.y;
	if (my < v2.y)
		my = v2.y;

	mz = v0.z;
	if (mz < v1.z)
		mz = v1.z;
	if (mz < v2.z)
		mz = v2.z;
}
