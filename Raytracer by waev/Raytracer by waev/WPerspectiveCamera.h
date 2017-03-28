#pragma once
#include "WCamera.h"
#include "WGeometricObject.h"
#include <list>
class WPerspectiveCamera :
	public WCamera
{
private:
	float d;
public:
	WPerspectiveCamera();
	~WPerspectiveCamera();
	void setDistance(float d);
	void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects);
};

