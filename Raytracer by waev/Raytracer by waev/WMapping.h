#pragma once
#include "WVector3.h"
class WMapping
{
public:
	WMapping();
	~WMapping();
	virtual void getPixelCoordinates(WVector3 &localHitPoint,
		int hres, int vres, int &row, int &column) = 0;
};

