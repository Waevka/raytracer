#include "WUtilities.h"
#include <math.h>
#include <iostream>

WVector3 calculateIntersectionPoint(float distance, WRay r) {
	if (distance == 25000) {
		std::cout << "\nNo point of intersection\n";
		distance = 0; // do exception
	}
	WVector3 result(r.getDirection());
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
