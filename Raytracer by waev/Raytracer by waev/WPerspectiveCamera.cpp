#include "WPerspectiveCamera.h"
#include <iostream>
#include "WViewPlane.h"
#include "WUtilities.h"


WPerspectiveCamera::WPerspectiveCamera(WWorld & wr) : WCamera("persp.tga", wr)
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
	this->viewPlaneHeight = viewPlane.getHeight();
	this->viewPlaneWidth = viewPlane.getWidth();
	this->pixelSize = viewPlane.getPixelSize();

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
			rays[i][j] = WRay(viewPlane.getRay().origin, newDirection);
		}
	}
}

WRay WPerspectiveCamera::generateSingleRay(WRay & ray, float xOffset, float yOffset, int i, int j)
{
	float newRayX = pixelSize*(i - viewPlaneWidth / 2 + 0.5f) + xOffset;
	float newRayY = pixelSize*(j - viewPlaneHeight / 2 + 0.5f) + yOffset;
	float newRayZ = d;
	WVector3 newDirection = WVector3(newRayX, newRayY, newRayZ);
	newDirection.normalize();
	return WRay(ray.origin, newDirection);
}
