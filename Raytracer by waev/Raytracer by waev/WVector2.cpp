#include "WVector2.h"
#include <string>
#include <sstream>



WVector2::WVector2()
{
	this->x = 0;
	this->y = 0;
}

WVector2::WVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

WVector2::WVector2(const WVector2 &v) : x(v.getX()), y(v.getY())
{
}


WVector2::~WVector2()
{
}

float WVector2::getX() const 
{
	return x;
}

float WVector2::getY() const
{
	return y;
}

std::string WVector2::toString()
{	
	std::stringstream ss;
	ss << "WVector2 [" << x << ", " << y << "]";
	return ss.str();
}
