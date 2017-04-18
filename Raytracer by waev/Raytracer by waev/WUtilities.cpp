#include "WUtilities.h"
#include <math.h>
#include <iostream>

WVector3 calculateIntersectionPoint(float distance, WRay r) {
	if (distance == 25000) {
		std::cout << "\nNo point of intersection\n";
		distance = 0; // do exception
	}
	WVector3 result(r.direction);
	result = result * distance;
	return result;
}

WColor getBackgroundCheckers(int x, int y, int width, int height)
{
	int slices = 6; //hardcoded just because
	int ratio = width / slices;
	int sliceX = x / ratio;
	int sliceY = y / ratio;
	float sliceZ = (float)sqrt(x*x + y*y);
	float sliceVal = 1.0f / 6;
	return WColor(sliceVal * sliceX, sliceVal * sliceY, 0.5);
}

WColor randomColor()
{
	float randfloat1 = (float)(rand() % 99 + 1) / 100.0f;
	float randfloat2 = (float)(rand() % 99 + 1) / 100.0f;
	float randfloat3 = (float)(rand() % 99 + 1) / 100.0f;
	return WColor(randfloat1, randfloat2, randfloat3);
}

WColor correctColor(WColor c)
{	
	float invGamma = 1.0f;
	WColor corrected;
	//if(viewplane.outofgamut)
	corrected = maxColorToOne(c);
	return corrected;
}

inline float max(float x0, float x1)
{
	return((x0 > x1) ? x0 : x1);
}

WColor maxColorToOne(const WColor & c)
{
	float maxVal = max(c.r, max(c.g, c.b));

	WColor newColor(c);
	if (maxVal > 1.0) {
		if (c.r > 1.0)
			newColor.r = 1.0f;
		if (c.g > 1.0)
			newColor.g = 1.0f;
		if (c.b > 1.0f)
			newColor.b = 1.0f;
	}

	
	/*if (maxVal > 1.0) {
		return (c / maxVal);
	}
	else {
		return (c);
	}*/
	return newColor;
}

WColor clampColor(const WColor & c)
{
	WColor clamped(c);

	if (c.r > 1.0 || c.g > 1.0 || c.b > 1.0) {
		clamped.r = 1.0;
		clamped.g = 1.0;
		clamped.b = 1.0;
	}

	return clamped;
}
