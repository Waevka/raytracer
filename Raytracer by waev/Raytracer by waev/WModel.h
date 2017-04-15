#pragma once
#include "WGeometricObject.h"
#include <vector>

class WModel :
	public WGeometricObject
{
public:
	WModel();
	~WModel();

	std::vector<WGeometricObject*> objects;

	virtual int Intersection(WRay &ray, float &dist, WShadingInfo &ws);
	virtual bool shadowHit(WRay &r, float &tmin);
	void addObject(WGeometricObject *t);
	void setMaterial(WMaterial *m);

};

