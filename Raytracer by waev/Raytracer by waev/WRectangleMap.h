#pragma once
#include "WMapping.h"
class WRectangleMap :
	public WMapping
{
public:
	WRectangleMap();
	~WRectangleMap();
	virtual void getTexelCoordinates(WVector3 &localHitPoint,
		int hres, int vres, int &row, int &column);
};

