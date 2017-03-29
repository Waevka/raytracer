#include "WColor.h"




WColor::WColor()
{
	this->r = 0.9f;
	this->g = 0.9f;
	this->b = 0.9f;
	this->a = 1.0f;
}

WColor::WColor(float r, float g, float b)
{
	this->r = r;
	this->b = b;
	this->g = g;
	this->a = 1.0f;
}

WColor::WColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

WColor::~WColor()
{
}

bool WColor::operator==(WColor corner)
{	
	if (r == corner.r && g == corner.g && b == corner.b && a == corner.a) return true;
	else return false;
}

bool WColor::operator!=(WColor corner)
{
	if (r == corner.r && g == corner.g && b == corner.b && a == corner.a) return false;
	else return true;
}
