#pragma once
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WViewPlane.h"
#include "WObjReader.h"
#include "WCamera.h"
#include "WLight.h"
#include <list>

class WWorld
{
private:
	WViewPlane viewPlane;
	std::list<WGeometricObject*> objects;
	std::list<WCamera*> cameras;
	std::list<WLight*> lights;
	WColor backgroundColor;
	WImageWriter imageWriter;
	WObjReader objReader;

public:
	WWorld();
	//WWorld()
	~WWorld();
	void draw();
	void addObject(WGeometricObject* o);
	void addCamera(WCamera* c);
};

