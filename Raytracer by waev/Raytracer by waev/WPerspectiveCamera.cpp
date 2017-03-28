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

void WPerspectiveCamera::draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects)
{
	WViewPlane viewPlane = WViewPlane(0.5f, TESTSIZE_W, TESTSIZE_H);
	viewPlane.setPixelSize(0.05f);

	WImage testImage(viewPlane.getWidth(), viewPlane.getHeight());

	//base ray for viewPlane
	WRay testRay(WVector3(0, 0, -40), WVector3(0, 0, 1.0f));

	//generate rays
	WRay **testRays = new WRay*[viewPlane.getWidth()];
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		testRays[i] = new WRay[viewPlane.getHeight()];
	}

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {
			float newRayX = viewPlane.getPixelSize()*(i - viewPlane.getWidth() / 2 + 0.5f);
			float newRayY = viewPlane.getPixelSize()*(j - viewPlane.getHeight() / 2 + 0.5f);
			float newRayZ = d;
			WVector3 newDirection = WVector3(newRayX, newRayY, newRayZ);
			newDirection.normalize();
			testRays[i][j] = WRay(testRay.getOrigin(), newDirection);
		}
	}

	//check all rays with objects
	bool anythingForThisPixelFound = false;
	WGeometricObject* currentBest = NULL;
	float distance = 400.0f;
	float bestDistance;
	int result;

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {

			anythingForThisPixelFound = false;
			currentBest = NULL;
			bestDistance = 400.0f;

			for (std::list<WGeometricObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {

				distance = 400.0f;
				result = (*iter)->Intersection(testRays[i][j], distance);
				if (result > 1) {
					if (distance < bestDistance) {
						bestDistance = distance;
						currentBest = (*iter);
						anythingForThisPixelFound = true;
					}
				}
			}

			if (anythingForThisPixelFound) {
				testImage.setPixel(currentBest->getColor(), i, j);
			}
			else {
				WColor backgroundColor = getBackgroundCheckers(i, j, viewPlane.getWidth(), viewPlane.getHeight());
				testImage.setPixel(backgroundColor, i, j);
			}
		}
	}

	imageWriter.writeImage(testImage, TESTSIZE_W, TESTSIZE_H, name);

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		delete[] testRays[i];
	}
	delete[] testRays;

	std::cout << "\nFinished - " << name;
}
