#pragma once
class WColor
{
public:
	float r;
	float g;
	float b;
	float a;
	WColor();
	WColor(float c);
	WColor(float r, float g, float b);
	WColor(float r, float g, float b, float a);
	WColor(const WColor &wc);
	~WColor();
	bool operator==(WColor corner);
	bool operator!=(WColor corner);
	WColor operator* (float f);
	WColor operator* (const WColor &wc);
	WColor operator+(const WColor &wc);
	WColor operator* (const float f) const;
};

