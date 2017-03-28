#pragma once
#include <string>
#include <list>
#include "WGeometricObject.h"
#include "WImageWriter.h"
class WCamera
{
private:
protected:
	WImageWriter imageWriter;
	std::string name;
public:
	virtual void draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects);
	WCamera();
	WCamera(std::string name);
	~WCamera();
};

