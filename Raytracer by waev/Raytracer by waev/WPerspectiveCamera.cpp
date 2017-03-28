#include "WPerspectiveCamera.h"
#include <iostream>
#include "WViewPlane.h"
#include "WUtilities.h"


WPerspectiveCamera::WPerspectiveCamera() : WCamera("persp.tga")
{
	this->d = 20;
}


WPerspectiveCamera::~WPerspectiveCamera()
{
	
}

void WPerspectiveCamera::setDistance(float d)
{
	this->d = d;
}

void WPerspectiveCamera::generateRays(WRay **& rays, WViewPlane &viewPlane)
{
	rays = new WRay*[viewPlane.getWidth()];
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		rays[i] = new WRay[viewPlane.getHeight()];
	}

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {
			float newRayX = viewPlane.getPixelSize()*(i - viewPlane.getWidth() / 2 + 0.5f);
			float newRayY = viewPlane.getPixelSize()*(j - viewPlane.getHeight() / 2 + 0.5f);
			float newRayZ = d;
			WVector3 newDirection = WVector3(newRayX, newRayY, newRayZ);
			newDirection.normalize();
			rays[i][j] = WRay(viewPlane.getRay().getOrigin(), newDirection);
		}
	}
}
