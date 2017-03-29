#include "WOrthoCamera.h"
#include <iostream>
#include "WGeometricObject.h"
#include "WViewPlane.h"
#include "WImage.h"
#include "WUtilities.h"
#include <list>


WOrthoCamera::WOrthoCamera() : WCamera("ortho.tga")
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
			float newRayX = viewPlane.getRay().getOrigin().getX() + viewPlane.getPixelSize()*(i - viewPlane.getWidth() / 2 + 0.5f);
			float newRayY = viewPlane.getRay().getOrigin().getY() + viewPlane.getPixelSize()*(j - viewPlane.getHeight() / 2 + 0.5f);
			float newRayZ = viewPlane.getRay().getOrigin().getZ();
			rays[i][j] = WRay(WVector3(newRayX, newRayY, newRayZ), viewPlane.getRay().getDirection());
		}
	}
}

WRay WOrthoCamera::generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j)
{
	float newRayX = ray.getOrigin().getX() + xOffset;
	float newRayY = ray.getOrigin().getY() + yOffset;
	float newRayZ = ray.getOrigin().getZ();
	return WRay(WVector3(newRayX, newRayY, newRayZ), ray.getDirection());
}
