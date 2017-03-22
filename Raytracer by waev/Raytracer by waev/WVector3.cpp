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

void WVector3::setX(float x)
{
	this->x = x;
}

void WVector3::setY(float y)
{
	this->y = y;
}

void WVector3::setZ(float z)
{
	this->z = z;
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

WVector3 WVector3::reflect(WVector3 normal)
{
	float dotNormal = 2 * this->dot(normal);
	WVector3 dotNormalVector = normal * dotNormal;
	WVector3 final(getX(), getY(), getZ());
	final = final - dotNormalVector;
	return final;
}

WVector3 WVector3::magProduct(WVector3 v, float f)
{
	return WVector3(v.getX() * f, v.getY() * f, v.getZ() * f);
}

WVector3 WVector3::toPoint()
{
	return WVector3(getX(), getY(), getZ());
}

WVector3 WVector3::lerp(WVector3 v, float t)
{	
	float nX = getX() + t * (v.getX() - getX());
	float nY = getY() + t * (v.getY() - getY());
	float nZ = getZ() + t * (v.getZ() - getZ());
	return WVector3(nX, nY, nZ);
}

WVector3 WVector3::operator* (float f)
{	
	WVector3 v(getX() * f, getY() * f, getZ() * f);
	return v;
}

WVector3 WVector3::operator*(WVector3 v)
{
	WVector3 v2(getX() * v.getX(), getY() * v.getY(), getZ() * v.getZ());
	return v2;
}

WVector3 WVector3::operator+(WVector3 v)
{
	WVector3 v2(getX() + v.getX(), getY() + v.getY(), getZ() + v.getZ());
	return v2;
}

WVector3 WVector3::operator-(WVector3 v)
{
	WVector3 v2(getX() - v.getX(), getY() - v.getY(), getZ() - v.getZ());
	return v2;
}

WVector3 WVector3::operator-()
{
	WVector3 v2(-getX(), -getY(), -getZ());
	return v2;
}

bool WVector3::operator==(WVector3 v)
{
	return (getX() == v.getX() && getY() == v.getY() && getZ() == v.getZ());
}

bool WVector3::operator!=(WVector3 v)
{
	return (getX() != v.getX() || getY() != v.getY() || getZ() != v.getZ());
}

WVector3 WVector3::operator/(float f)
{
	WVector3 v2(getX(), getY(), getZ());
	float inverse = 1.0f / f;
	v2.setX(v2.getX() * inverse);
	v2.setY(v2.getY() * inverse);
	v2.setZ(v2.getZ() * inverse);
	return v2;
}
