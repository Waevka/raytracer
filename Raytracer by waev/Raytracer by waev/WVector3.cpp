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

WVector3::WVector3(float xyz)
{	
	this->x = xyz;
	this->y = xyz;
	this->z = xyz;
}

WVector3::WVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

WVector3::WVector3(const WVector3& v) : x(v.x), y(v.y), z(v.z)
{
}

WVector3::WVector3(const WVector3 & v1, const WVector3 & v2) :
	x(v2.x - v1.x), y(v2.y - v1.y), z(v2.z - v1.z)
{
}


WVector3::~WVector3()
{
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

void WVector3::add(WVector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void WVector3::subtract(WVector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
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

float WVector3::dot(WVector3 &v)
{
	float d = (x * v.x + y * v.y + z * v.z);
	return d;
}

WVector3 WVector3::cross(WVector3 v)
{
	WVector3 nv(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
	return nv;
}

WVector3 WVector3::reflect(WVector3 normal)
{
	float dotNormal = 2 * this->dot(normal);
	WVector3 dotNormalVector = normal * dotNormal;
	WVector3 final(x, y, z);
	final = final - dotNormalVector;
	return final;
}

WVector3 WVector3::magProduct(WVector3 v, float f)
{
	return WVector3(v.x * f, v.y * f, v.z * f);
}

WVector3 WVector3::toPoint()
{
	return WVector3(x, y, z);
}

WVector3 WVector3::lerp(WVector3 v, float t)
{	
	float nX = x + t * (v.x - x);
	float nY = y + t * (v.y - y);
	float nZ = z + t * (v.z - z);
	return WVector3(nX, nY, nZ);
}

WVector3 WVector3::hat()
{	
	float length = sqrt(x*x + y*y + z*z);
	x /= length;
	y /= length;
	z /= length;
	return (*this);
}

float WVector3::distance(WVector3 v)
{
	float xd = x - v.x;
	float yd = y - v.y;
	float zd = z - v.z;
	return sqrt(xd*xd + yd*yd + zd*zd);
}

WVector3 WVector3::operator* (float f)
{	
	WVector3 v(x * f, y * f, z * f);
	return v;
}

WVector3 WVector3::operator*(WVector3 v)
{
	WVector3 v2(x * v.x, y * v.y, z * v.z);
	return v2;
}

WVector3 WVector3::operator+(WVector3 v)
{
	WVector3 v2(x + v.x, y + v.y, z + v.z);
	return v2;
}

WVector3 WVector3::operator-(WVector3 v)
{
	WVector3 v2(x - v.x, y - v.y, z - v.z);
	return v2;
}

WVector3 WVector3::operator-()
{
	WVector3 v2(-x, -y, -z);
	return v2;
}

bool WVector3::operator==(WVector3 v)
{
	return (x == v.x && y == v.y && z == v.z);
}

bool WVector3::operator!=(WVector3 v)
{
	return (x != v.x || y != v.y || z != v.z);
}

WVector3 WVector3::operator/(float f)
{
	WVector3 v2(x, y, z);
	float inverse = 1.0f / f;
	v2.x = v2.x * inverse;
	v2.y = v2.y * inverse;
	v2.z = v2.z * inverse;
	return v2;
}
