#pragma once
#include "WRay.h"
class WBoundingBox
{
public:
	WBoundingBox();
	WBoundingBox(float nx0, float nx1, float ny0, float ny1, float nz0, float nz1);
	~WBoundingBox();

	double x0, x1, y0, y1, z0, z1;

	bool hit(const WRay &r) const;
};

