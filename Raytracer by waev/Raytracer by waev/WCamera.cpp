#include "WCamera.h"
#include "WUtilities.h"
#include "WWorld.h"
#include "WMatteMaterial.h"
#include <iostream>

void WCamera::draw(int TESTSIZE_W, int TESTSIZE_H, WViewPlane &viewPlane)
{
	WImage testImage(viewPlane.getWidth(), viewPlane.getHeight());

	//generate rays
	WRay **testRays;
	generateRays(testRays, viewPlane);

	//check all rays with objects
	intersectRays(viewPlane, testRays, testImage);

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

void WCamera::intersectRays(WViewPlane &viewPlane, WRay** &rays, WImage &testImage)
{	
	WShadingInfo shadingInfo(world);
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		for (int j = 0; j < viewPlane.getHeight(); j++) {
			if (i == 367 && j == 358) {
				std::cout << "hui";
			}
			WColor pixelColor = intersectSingleRay(rays[i][j], shadingInfo, i, j, viewPlane, 0);

			testImage.setPixel(pixelColor, i, j);
		}
	}
}

WColor WCamera::rayAliasing(int currentLevel)
{
	return WColor();
}

WColor WCamera::intersectSingleRay(WRay &ray, WShadingInfo &shadingInfo, int i, int j, WViewPlane &viewPlane, int aliasingLevel)
{	
	WColor pixelColor;
	std::vector<WGeometricObject*> &objects = shadingInfo.world.objects;
	if (aliasingLevel >= this->aliasingLevel) {

		bool anythingForThisPixelFound = false;
		float distance = 400.0f;
		float bestDistance = 400.0f;
		int result;
		WMaterial *material = NULL;
		WVector3 normal;
		WVector3 localHitPoint;

		for (int j = 0; j < objects.size(); j++) {

			result = objects[j]->Intersection(ray, distance, shadingInfo);
			if (result > 0 && distance < bestDistance ) {
				bestDistance = distance;
				normal = shadingInfo.normal;
				material = shadingInfo.material;
				localHitPoint = shadingInfo.localHitPoint;
				shadingInfo.hitPoint = ray.origin + (ray.direction * bestDistance);
				anythingForThisPixelFound = true;
			}
		}

		if (anythingForThisPixelFound) {
			shadingInfo.t = bestDistance;
			shadingInfo.material = material;
			shadingInfo.normal = normal;
			shadingInfo.localHitPoint = localHitPoint;
			pixelColor = shadingInfo.material->shade(shadingInfo);
			//pixelColor = static_cast<WMatteMaterial*>(shadingInfo.material)->getCd();
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

		WColor middle		= intersectSingleRay(ray,				shadingInfo, i, j, viewPlane, this->aliasingLevel);
		WColor topLeft		= intersectSingleRay(topLeftRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel);
		WColor topRight		= intersectSingleRay(topRightRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel);
		WColor bottomLeft	= intersectSingleRay(bottomLeftRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel);
		WColor bottomRight	= intersectSingleRay(bottomRightRay,	shadingInfo, i, j, viewPlane, this->aliasingLevel);

		offset = (float)(viewPlane.getPixelSize() * pow(0.5f, aliasingLevel + 2)); //TODO: offset/2

		if (middle != topLeft) {
			intersectSingleRay(topLeftRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1);
			topLeftRay = generateSingleRay(ray, -offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(topRightRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1);
			topRightRay = generateSingleRay(ray, offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomLeftRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1);
			bottomLeftRay = generateSingleRay(ray, -offset, -offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomRightRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1);
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

WCamera::WCamera(std::string name, WWorld &wr) : world(wr)
{
	this->name = name;
	aliasingLevel = 5;
}


WCamera::~WCamera()
{
}
