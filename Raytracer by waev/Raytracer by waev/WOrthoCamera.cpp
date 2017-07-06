#include "WOrthoCamera.h"
#include <iostream>
#include "WGeometricObject.h"
#include "WViewPlane.h"
#include "WImage.h"
#include "WUtilities.h"
#include <list>


WOrthoCamera::WOrthoCamera(WWorld & wr) : WCamera("ortho.tga", wr)
{
	
}


WOrthoCamera::~WOrthoCamera()
{
}

void WOrthoCamera::generateRays(WRay **& rays, WViewPlane & viewPlane)
{
	rays = new WRay*[viewPlane.getWidth()];
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		rays[i] = new WRay[viewPlane.getHeight()];
	}

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {
			float newRayX = viewPlane.getRay().origin.x + viewPlane.getPixelSize()*(i - viewPlane.getWidth() / 2 + 0.5f);
			float newRayY = viewPlane.getRay().origin.y + viewPlane.getPixelSize()*(j - viewPlane.getHeight() / 2 + 0.5f);
			float newRayZ = viewPlane.getRay().origin.z;
			rays[i][j] = WRay(WVector3(newRayX, newRayY, newRayZ), viewPlane.getRay().direction);
		}
	}
}

WRay WOrthoCamera::generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j)
{
	float newRayX = ray.origin.x + xOffset;
	float newRayY = ray.origin.y + yOffset;
	float newRayZ = ray.origin.z;
	return WRay(WVector3(newRayX, newRayY, newRayZ), ray.direction);
}

WRay WOrthoCamera::generateSinglePathBounceRay(WRay & ray, float xOffset, float yOffset, int i, int j, WVector3 hitPoint)
{
	return WRay();
}
