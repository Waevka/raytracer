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
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {

			WColor pixelColor = intersectSingleRay(rays[i][j], objects, i, j, viewPlane, 0);

			testImage.setPixel(pixelColor, i, j);
		}
	}
}

WColor WCamera::rayAliasing(int currentLevel)
{
	return WColor();
}

WColor WCamera::intersectSingleRay(WRay &ray, std::list<WGeometricObject*> &objects, int i, int j, WViewPlane &viewPlane, int aliasingLevel)
{	
	WColor pixelColor;
	if (aliasingLevel >= this->aliasingLevel) {

		bool anythingForThisPixelFound = false;
		WGeometricObject* currentBest = NULL;
		float distance = 400.0f;
		float bestDistance = 400.0f;
		int result;

		for (std::list<WGeometricObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {

			distance = 400.0f;
			result = (*iter)->Intersection(ray, distance);
			if (result > 1) {
				if (distance < bestDistance) {
					bestDistance = distance;
					currentBest = (*iter);
					anythingForThisPixelFound = true;
				}
			}
		}

		if (anythingForThisPixelFound) {
			pixelColor = currentBest->getColor();
		}
		else {
			pixelColor = getBackgroundCheckers(i, j, viewPlane.getWidth(), viewPlane.getHeight());

		}

	}
	else {
		float offset = (float)(viewPlane.getPixelSize() * pow(0.5f, aliasingLevel+1));
		WRay topLeftRay		= generateSingleRay(ray, -	offset,		offset, i, j);
		WRay topRightRay	= generateSingleRay(ray,	offset,		offset, i, j);
		WRay bottomLeftRay	= generateSingleRay(ray, -	offset, -	offset, i, j);
		WRay bottomRightRay = generateSingleRay(ray,	offset, -	offset, i, j);
		WColor topLeft		= intersectSingleRay(topLeftRay,		objects, i, j, viewPlane, aliasingLevel + 1);
		WColor topRight		= intersectSingleRay(topRightRay,		objects, i, j, viewPlane, aliasingLevel + 1);
		WColor bottomLeft	= intersectSingleRay(bottomLeftRay,		objects, i, j, viewPlane, aliasingLevel + 1);
		WColor bottomRight	= intersectSingleRay(bottomRightRay,	objects, i, j, viewPlane, aliasingLevel + 1);
		float r = (float)((topLeft.r + topRight.r + bottomLeft.r + bottomRight.r) / 4.0f);
		float g = (float)((topLeft.g + topRight.g + bottomLeft.g + bottomRight.g) / 4.0f);
		float b = (float)((topLeft.b + topRight.b + bottomLeft.b + bottomRight.b) / 4.0f);
		float a = (float)((topLeft.a + topRight.a + bottomLeft.a + bottomRight.a) / 4.0f);
		pixelColor = WColor(r, g, b, a);
	}
	return pixelColor;
}

WCamera::WCamera()
{
	this->name = "camera.tga";
	aliasingLevel = 2;
}

WCamera::WCamera(std::string name)
{
	this->name = name;
	aliasingLevel = 2;
}


WCamera::~WCamera()
{
}