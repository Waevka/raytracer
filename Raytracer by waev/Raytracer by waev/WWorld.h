#pragma once
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WViewPlane.h"
#include "WCamera.h"
#include <list>

class WWorld
{
private:
	WViewPlane viewPlane;
	std::list<WGeometricObject*> objects;
	std::list<WCamera*> cameras;
	WColor backgroundColor;
	WImageWriter imageWriter;

public:
	WWorld();
	~WWorld();
	void draw();
	void addObject(WGeometricObject* o);
	void addCamera(WCamera* c);
};

