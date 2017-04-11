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
	WShadingInfo shadingInfo;
	WVector3 normal;
	WVector3 localHitPoint;
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
					shadingInfo.hitObject = true;
					shadingInfo.material = (*currentBest).getMaterial();
					shadingInfo.hitPoint = ray.getOrigin() + bestDistance * ray.getDistance();
					shadingInfo.color = (*currentBest).getColor();
					normal = shadingInfo.normal;
					localHitPoint = shadingInfo.localHitPoint;
					anythingForThisPixelFound = true;
				}
			}
		}

		if (anythingForThisPixelFound) {
			shadingInfo.t = bestDistance;
			shadingInfo.localHitPoint = localHitPoint;
			pixelColor = shadingInfo.material->shade(shadingInfo);
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

		WColor middle		= intersectSingleRay(ray,				objects, i, j, viewPlane, this->aliasingLevel);
		WColor topLeft		= intersectSingleRay(topLeftRay,		objects, i, j, viewPlane, this->aliasingLevel);
		WColor topRight		= intersectSingleRay(topRightRay,		objects, i, j, viewPlane, this->aliasingLevel);
		WColor bottomLeft	= intersectSingleRay(bottomLeftRay,		objects, i, j, viewPlane, this->aliasingLevel);
		WColor bottomRight	= intersectSingleRay(bottomRightRay,	objects, i, j, viewPlane, this->aliasingLevel);

		offset = (float)(viewPlane.getPixelSize() * pow(0.5f, aliasingLevel + 2)); //TODO: offset/2

		if (middle != topLeft) {
			intersectSingleRay(topLeftRay, objects, i, j, viewPlane, aliasingLevel + 1);
			topLeftRay = generateSingleRay(ray, -offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(topRightRay, objects, i, j, viewPlane, aliasingLevel + 1);
			topRightRay = generateSingleRay(ray, offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomLeftRay, objects, i, j, viewPlane, aliasingLevel + 1);
			bottomLeftRay = generateSingleRay(ray, -offset, -offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomRightRay, objects, i, j, viewPlane, aliasingLevel + 1);
			bottomRightRay = generateSingleRay(ray, offset, -offset, i, j);
		}

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
	aliasingLevel = 5;
}

WCamera::WCamera(std::string name)
{
	this->name = name;
	aliasingLevel = 5;
}


WCamera::~WCamera()
{
}
