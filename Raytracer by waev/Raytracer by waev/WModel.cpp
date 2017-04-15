#include "WModel.h"



WModel::WModel() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
}


WModel::~WModel()
{
}

int WModel::Intersection(WRay & ray, float & dist, WShadingInfo & ws)
{
	return 0;
}

bool WModel::shadowHit(WRay & r, float & tmin)
{
	return false;
}

void WModel::addObject(WGeometricObject * t)
{
	objects.push_back(t);
}

void WModel::setMaterial(WMaterial * m)
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->setMaterial(m);
	}
}
