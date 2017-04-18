#include "WModel.h"
#include "WPhong.h"
#include "WUtilities.h"


WModel::WModel() : WGeometricObject(WColor(1.0f, 1.0f, 1.0f, 1.0f)), boundingBox(NULL)
{
}

WModel::WModel(std::vector<WGeometricObject*> ol) : WGeometricObject(), objects(ol), boundingBox(NULL)
{
}


WModel::~WModel()
{
}

int WModel::Intersection(WRay & ray, float & dist, WShadingInfo & ws)
{	
	if (!getBoundingBox()->hit(ray))
		return 0;

	WVector3 localHitPoint;
	WVector3 normal;
	int bestObject = 0;
	int anythingForThisPixelFound = 0;
	float distance = 400.0f;
	float bestDistance = 400.0f;
	int result;

	for (int j = 0; j < objects.size(); j++) {

		result = objects[j]->Intersection(ray, distance, ws);
		if (result > 0 && distance < bestDistance) {
			bestDistance = distance;
			bestObject = j;
			ws.material = objects[bestObject]->getMaterial();
			ws.color = objects[bestObject]->getColor();
			ws.hitPoint = ray.origin + (ray.direction * bestDistance);
			localHitPoint = ws.localHitPoint;
			normal = ws.normal;
			anythingForThisPixelFound = 1;
		}
	}

	if (anythingForThisPixelFound) {
		ws.hitObject = true;
		ws.ray = ray;
		ws.normal = normal;
		ws.localHitPoint = localHitPoint;
		ws.t = bestDistance;
		dist = bestDistance;
		ws.name = name;
	}

	return anythingForThisPixelFound;
}

bool WModel::shadowHit(WRay & r, float & tmin)
{
	if (!getBoundingBox()->hit(r))
		return false;

	float tmin2 = 400.0f;
	bool hit = false;

	for (int i = 0; i < objects.size(); i++) {
		bool result = objects[i]->shadowHit(r, tmin2);
		if (result && tmin2 < tmin) {
			tmin = tmin2;
			hit = true;
		}
	}

	return hit;
}

void WModel::addObject(WGeometricObject * t)
{
	objects.push_back(t);
	delete[] boundingBox;
	boundingBox = NULL;
}

void WModel::setMaterial(WMaterial * m)
{
	for (int i = 0; i < objects.size(); i++) {
		/*WPhong *triangleMat = new WPhong();
		triangleMat->setKa(0.25f);
		triangleMat->setKd(0.65f);
		triangleMat->setKs(0.2f);
		triangleMat->setExp(5);
		triangleMat->setCd(randomColor());*/
		objects[i]->setMaterial(m);
	}
}

void WModel::calculateBoundingBox()
{	
	float x0 = 32000;
	float y0 = 32000;
	float z0 = 32000;

	for (int i = 0; i < objects.size(); i++) {
		float nx = 32000;
		float ny = 32000;
		float nz = 32000;
		objects[i]->minXYZ(nx, ny, nz);

		if (nx < x0) x0 = nx;
		if (ny < y0) y0 = ny;
		if (nz < z0) z0 = nz;
	}

	float x1 = -32000;
	float y1 = -32000;
	float z1 = -32000;
	for (int i = 0; i < objects.size(); i++) {
		float nx = -32000;
		float ny = -32000;
		float nz = -32000;
		objects[i]->maxXYZ(nx, ny, nz);

		if (nx > x1) x1 = nx;
		if (ny > y1) y1 = ny;
		if (nz > z1) z1 = nz;
	}

	boundingBox = new WBoundingBox(x0, x1, y0, y1, z0, z1);
}

WBoundingBox * WModel::getBoundingBox()
{	
	if (boundingBox == NULL)
		calculateBoundingBox();
	return boundingBox;
}
