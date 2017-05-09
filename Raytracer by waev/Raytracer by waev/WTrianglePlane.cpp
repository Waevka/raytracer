#include "WTrianglePlane.h"
#include "WTriangle.h"


WTrianglePlane::WTrianglePlane(WVector3 & center, float width, float height, int direction) : WModel(), center(center), width(width), height(height), direction(direction)
{
	switch (this->direction) {
	case 0:
		createUpPlane();
		break;
	case 1:
		createDownPlane();
		break;
	case 2:
		createLeftPlane();
		break;
	case 3:
		createRightPlane();
		break;
	case 4:
		createFrontPlane();
		break;
	default:
		createUpPlane();
		break;
	}
}

WTrianglePlane::~WTrianglePlane()
{
}

int WTrianglePlane::Intersection(WRay & ray, float & dist, WShadingInfo & ws)
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
		localHitPoint.x = 0.0f;
		localHitPoint.y += 0.5*width;
		localHitPoint.y /= width;
		localHitPoint.z = -localHitPoint.z; // turn texture upside down for easier editing
		localHitPoint.z += 0.5*height;
		localHitPoint.z /= height;
		ws.localHitPoint = localHitPoint;
		ws.t = bestDistance;
		dist = bestDistance;
		ws.name = name;
	}

	return anythingForThisPixelFound;
}

void WTrianglePlane::createUpPlane()
{
	WTriangle *first = new WTriangle(
		WVector3(center.x, center.y - 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(1.0f, 0.0f, 0.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x, center.y + 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(1.0f, 0.0f, 0.0f)
	);
	addObject(first);
	addObject(second);
}

void WTrianglePlane::createDownPlane()
{
	WTriangle *first = new WTriangle(
		WVector3(center.x, center.y - 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(-1.0f, 0.0f, 0.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x, center.y + 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y - 0.5*width, center.z + 0.5*height),
		WVector3(center.x, center.y + 0.5*width, center.z - 0.5*height),
		WVector3(-1.0f, 0.0f, 0.0f)
	);
	addObject(first);
	addObject(second);
}

void WTrianglePlane::createLeftPlane()
{
	WTriangle *first = new WTriangle(
		WVector3(center.x - 0.5*width, center.y, center.z - 0.5*height),
		WVector3(center.x + 0.5*width, center.y , center.z - 0.5*height),
		WVector3(center.x - 0.5*width, center.y , center.z + 0.5*height),
		WVector3(0.0f, -1.0f, 0.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x + 0.5*width, center.y, center.z + 0.5*height),
		WVector3(center.x - 0.5*width, center.y, center.z + 0.5*height),
		WVector3(center.x + 0.5*width, center.y , center.z - 0.5*height),
		WVector3(0.0f, -1.0f, 0.0f)
	);
	addObject(first);
	addObject(second);
}

void WTrianglePlane::createRightPlane()
{
	WTriangle *first = new WTriangle(
		WVector3(center.x - 0.5*width, center.y, center.z - 0.5*height),
		WVector3(center.x + 0.5*width, center.y, center.z - 0.5*height),
		WVector3(center.x - 0.5*width, center.y, center.z + 0.5*height),
		WVector3(0.0f, 1.0f, 0.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x + 0.5*width, center.y, center.z + 0.5*height),
		WVector3(center.x - 0.5*width, center.y, center.z + 0.5*height),
		WVector3(center.x + 0.5*width, center.y, center.z - 0.5*height),
		WVector3(0.0f, 1.0f, 0.0f)
	);
	addObject(first);
	addObject(second);
}

void WTrianglePlane::createFrontPlane()
{
	WTriangle *first = new WTriangle(
		WVector3(center.x - 0.5*width, center.y - 0.5*height, center.z+0.0001f),
		WVector3(center.x + 0.5*width, center.y - 0.5*height, center.z),
		WVector3(center.x - 0.5*width, center.y + 0.5*height, center.z),
		WVector3(0.0f, 0.0f, 1.0f)
	);
	WTriangle *second = new WTriangle(
		WVector3(center.x + 0.5*width, center.y + 0.5*height, center.z),
		WVector3(center.x - 0.5*width, center.y + 0.5*height, center.z),
		WVector3(center.x + 0.5*width, center.y - 0.5*height, center.z),
		WVector3(0.0f, 0.0f, 1.0f)
	);
	addObject(first);
	addObject(second);
}
