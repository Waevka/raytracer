#pragma once
#include <string>
#include <list>
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WShadingInfo.h"
#include "WViewPlane.h"
class WCamera
{
private:
	int aliasingLevel;
protected:
	WImageWriter imageWriter;
	std::string name;
	WWorld &world;
public:
	virtual void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects, WViewPlane &viewPlane);
	virtual void generateRays(WRay** &rays, WViewPlane &viewPlane);
	virtual WRay generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j) = 0;
	virtual void intersectRays(WViewPlane &viewPlane, std::list<WGeometricObject*> &objects, WRay** &rays, WImage &testImage);
	virtual WColor rayAliasing(int currentLevel);
	virtual WColor intersectSingleRay(WRay &ray, std::list<WGeometricObject*> &objects, int i, int j, WViewPlane &viewPlane, int aliasingLevel);
	WCamera(std::string name, WWorld &wr);
	~WCamera();
};

