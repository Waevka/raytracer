#include "WVector3.h"
#include <string>
#include <sstream>



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
