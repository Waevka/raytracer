#pragma once
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WViewPlane.h"
#include <list>

class WWorld
{
private:
	WViewPlane viewPlane;
	std::list<WGeometricObject*> objects;
	WColor backgroundColor;
	WImageWriter imageWriter;

public:
	WWorld();
	~WWorld();
	void draw();
	void addObject(WGeometricObject* o);
};

