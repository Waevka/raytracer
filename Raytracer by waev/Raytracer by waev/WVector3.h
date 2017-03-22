#pragma once
#include <string>
class WVector3
{
private:
	float x;
	float y;
	float z;
public:
	WVector3();
	WVector3(float x, float y, float z);
	WVector3(const WVector3 &v);
	~WVector3();

	float getX() const;
	float getY() const;
	float getZ() const;

	std::string toString();
};

