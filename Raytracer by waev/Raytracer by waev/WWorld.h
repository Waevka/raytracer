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
	std::list<WCamera*> cameras;
	WColor backgroundColor;
	WImageWriter imageWriter;
	WObjReader objReader;

public:
	WWorld();
	~WWorld();
	void draw();
	void addObject(WGeometricObject* o);
	void addCamera(WCamera* c);
	void addLight(WLight* l);
	WLight *ambient;
	std::vector<WLight*> lights;
	std::vector<WGeometricObject*> objects;
};

