#pragma once
#include "WCamera.h"
#include "WGeometricObject.h"
#include <list>
class WPerspectiveCamera :
	public WCamera
{
public:
	WPerspectiveCamera();
	~WPerspectiveCamera();
	void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects);
};

