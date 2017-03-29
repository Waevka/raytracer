#pragma once
class WColor
{
public:
	float r;
	float g;
	float b;
	float a;
	WColor();
	WColor(float r, float g, float b);
	WColor(float r, float g, float b, float a);
	~WColor();
	bool operator==(WColor corner);
	bool operator!=(WColor corner);
};

