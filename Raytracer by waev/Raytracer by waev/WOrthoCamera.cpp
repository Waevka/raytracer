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
			float newRayX = viewPlane.getRay().getOrigin().x + viewPlane.getPixelSize()*(i - viewPlane.getWidth() / 2 + 0.5f);
			float newRayY = viewPlane.getRay().getOrigin().y + viewPlane.getPixelSize()*(j - viewPlane.getHeight() / 2 + 0.5f);
			float newRayZ = viewPlane.getRay().getOrigin().z;
			rays[i][j] = WRay(WVector3(newRayX, newRayY, newRayZ), viewPlane.getRay().getDirection());
		}
	}
}

WRay WOrthoCamera::generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j)
{
	float newRayX = ray.getOrigin().x + xOffset;
	float newRayY = ray.getOrigin().y + yOffset;
	float newRayZ = ray.getOrigin().z;
	return WRay(WVector3(newRayX, newRayY, newRayZ), ray.getDirection());
}
