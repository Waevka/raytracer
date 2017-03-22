#include "WVector3.h"
#include <string>
#include <sstream>
#include <math.h>



WVector3::WVector3()
{	
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

WVector3::WVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

WVector3::WVector3(const WVector3& v) : x(v.getX()), y(v.getY()), z(v.getZ())
{
}

WVector3::WVector3(const WVector3 & v1, const WVector3 & v2) :
	x(v2.getX() - v1.getX()), y(v2.getY() - v1.getY()), z(v2.getZ() - v1.getZ())
{
}


WVector3::~WVector3()
{
}

float WVector3::getX() const
{
	return x;
}

float WVector3::getY() const
{
	return y;
}

float WVector3::getZ() const
{
	return z;
}

std::string WVector3::toString()
{
	std::stringstream ss;
	ss << "WVector3 [" << x << ", " << y << ", " << z << "]";
	return ss.str();
}

float WVector3::getLength()
{
	float l = (float)sqrt(x*x + y*y + z*z);
	return l;
}

float WVector3::getLengthSquared()
{
	float l = (float)(x*x + y*y + z*z);
	return l;
}

void WVector3::divide(float n)
{
	if (n != 0) {
		this->x /= n;
		this->y /= n;
		this->z /= n;
	}
}

void WVector3::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

void WVector3::add(WVector3 v)
{
	x += v.getX();
	y += v.getY();
	z += v.getZ();
}

void WVector3::subtract(WVector3 v)
{
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
}

void WVector3::mag(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

void WVector3::normalize()
{
	float n = getLength();
	if (n != 0) {
		divide(n);
	}
	else {

	}
}

WVector3 WVector3::normalizeProduct()
{
	WVector3 v(x, y, z);
	float n = getLength();
	if (n != 0) {
		v.divide(n);
		return v;
	}
	else {
		// exception
		return v;
	}
}

float WVector3::dot(WVector3 v)
{
	float d = (x * v.getX() + y * v.getY() + z * v.getZ());
	return d;
}

WVector3 WVector3::cross(WVector3 v)
{
	WVector3 nv(
		y * v.getZ() - z * v.getY(),
		z * v.getX() - x * v.getZ(),
		x * v.getY() - y * v.getX());
	return nv;
}
