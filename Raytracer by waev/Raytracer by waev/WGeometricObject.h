#pragma once
#include "WColor.h"
#include "WMaterial.h"
#include "WRay.h"

class WGeometricObject
{
private:
	WColor color;
	WMaterial *material;
public:
	WGeometricObject();
	WGeometricObject(WColor c);
	~WGeometricObject();
	WColor getColor();
	WMaterial* getMaterial();
	void setMaterial(WMaterial *m);
	virtual int Intersection(WRay &ray, float & dist, WShadingInfo &ws);
	virtual bool shadowHit(WRay &r, float &tmin);
	virtual void minXYZ(float &mx, float &my, float &mz);
	virtual void maxXYZ(float &mx, float &my, float &mz);
};

