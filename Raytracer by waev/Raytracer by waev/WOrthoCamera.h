#pragma once
#include "WCamera.h"
class WOrthoCamera :
	public WCamera
{
public:
	WOrthoCamera();
	~WOrthoCamera();
	void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects);
};

