#include "WCamera.h"
#include "WUtilities.h"
#include <iostream>

void WCamera::draw(int TESTSIZE_W, int TESTSIZE_H, std::list<WGeometricObject*> &objects, WViewPlane &viewPlane)
{
	WImage testImage(viewPlane.getWidth(), viewPlane.getHeight());

	//generate rays
	WRay **testRays;
	generateRays(testRays, viewPlane);

	//check all rays with objects
	intersectRays(viewPlane, objects, testRays, testImage);

	imageWriter.writeImage(testImage, TESTSIZE_W, TESTSIZE_H, name);

	for (int i = 0; i < viewPlane.getWidth(); i++) {
		delete[] testRays[i];
	}
	delete[] testRays;

	std::cout << "\nFinished - " << name;
}

void WCamera::generateRays(WRay **& rays, WViewPlane &viewPlane)
{

}

void WCamera::intersectRays(WViewPlane &viewPlane, std::list<WGeometricObject*> &objects, WRay** &rays, WImage &testImage)
{
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
				result = (*iter)->Intersection(rays[i][j], distance);
				if (result > 1) {
					if (distance < bestDistance) {
						bestDistance = distance;
						currentBest = (*iter);
						anythingForThisPixelFound = true;
					}
				}
			}

			WColor pixelColor;

			if (anythingForThisPixelFound) {
				pixelColor = currentBest->getColor();
			}
			else {
				pixelColor = getBackgroundCheckers(i, j, viewPlane.getWidth(), viewPlane.getHeight());

			}

			testImage.setPixel(pixelColor, i, j);
		}
	}
}

WCamera::WCamera()
{
}

WCamera::WCamera(std::string name)
{
	this->name = name;
}


WCamera::~WCamera()
{
}
