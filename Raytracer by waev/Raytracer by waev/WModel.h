#pragma once
#include "WGeometricObject.h"
#include "WBoundingBox.h"
#include <vector>

class WModel :
	public WGeometricObject
{
private:
	WBoundingBox *boundingBox;
public:
	WModel();
	WModel(std::vector<WGeometricObject*> ol);
	~WModel();

	std::vector<WGeometricObject*> objects;
	std::string name;

	virtual int Intersection(WRay &ray, float &dist, WShadingInfo &ws);
	virtual bool shadowHit(WRay &r, float &tmin);
	void addObject(WGeometricObject *t);
	void setMaterial(WMaterial *m);
	void calculateBoundingBox();
	WBoundingBox* getBoundingBox();

};

