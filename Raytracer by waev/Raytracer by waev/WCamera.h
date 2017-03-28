#pragma once
#include <string>
#include <list>
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WViewPlane.h"
class WCamera
{
private:
protected:
	WImageWriter imageWriter;
	std::string name;
public:
	virtual void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects, WViewPlane &viewPlane);
	virtual void generateRays(WRay** &rays, WViewPlane &viewPlane);
	virtual void intersectRays(WViewPlane &viewPlane, std::list<WGeometricObject*> &objects, WRay** &rays, WImage &testImage);
	WCamera();
	WCamera(std::string name);
	~WCamera();
};

