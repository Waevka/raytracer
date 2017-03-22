#pragma once
#include <string>
class WVector2
{	
private:
	float x;
	float y;
public:
	WVector2();
	WVector2(float x, float y);
	WVector2(const WVector2 &v);
	WVector2(const WVector2 &v1, const WVector2 &v2);
	~WVector2();

	float getX() const;
	float getY() const;

	std::string toString();
};

