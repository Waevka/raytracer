#include "WModel.h"



WModel::WModel() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f))
{
}

WModel::WModel(std::vector<WGeometricObject*> ol) : WGeometricObject()
{
	objects = ol;
}


WModel::~WModel()
{
}

int WModel::Intersection(WRay & ray, float & dist, WShadingInfo & ws)
{	
	WVector3 localHitPoint;
	int bestObject = 0;
	int anythingForThisPixelFound = 0;
	float distance = 400.0f;
	float bestDistance = 400.0f;
	int result;

	for (int j = 0; j < objects.size(); j++) {

		distance = 400.0f;
		result = objects[j]->Intersection(ray, distance, ws);
		if (result > 1 && distance < bestDistance) {
			bestDistance = distance;
			bestObject = j;
			anythingForThisPixelFound = 1;
		}
	}

	if (anythingForThisPixelFound && bestDistance < dist) {
		ws.hitObject = true;
		ws.material = objects[bestObject]->getMaterial();
		ws.hitPoint = ray.origin + ray.direction * bestDistance;
		ws.color = objects[bestObject]->getColor();
		ws.ray = ray;
		ws.t = bestDistance;
		dist = bestDistance;
	}

	return anythingForThisPixelFound;
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
