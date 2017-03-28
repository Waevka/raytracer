#include "WUtilities.h"
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
