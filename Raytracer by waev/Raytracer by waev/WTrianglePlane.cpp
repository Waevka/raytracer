#include "WTrianglePlane.h"
#include "WTriangle.h"


WTrianglePlane::WTrianglePlane(WVector3 & center, float width, float height) : WModel(), center(center), width(width), height(height)
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
