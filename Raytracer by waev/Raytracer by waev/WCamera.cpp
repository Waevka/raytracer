#include "WCamera.h"
#include "WUtilities.h"
#include "WWorld.h"
#include "WMatteMaterial.h"
#include <iostream>

void WCamera::draw(int TESTSIZE_W, int TESTSIZE_H, WViewPlane &viewPlane)
{
	WImage testImage(viewPlane.getWidth(), viewPlane.getHeight());
	this->viewPlane = &viewPlane;
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
			shadingInfo.rayBounces = 0;
			WPath *path = new WPath();
			WColor pixelColor = intersectSingleRay(rays[i][j], shadingInfo, i, j, viewPlane, 0, path);
			pixelColor = correctColor(pixelColor);
			testImage.setPixel(pixelColor, i, j);
		}
	}
}

WColor WCamera::rayAliasing(int currentLevel)
{
	return WColor();
}

WColor WCamera::intersectSingleRay(WRay &ray, WShadingInfo &shadingInfo, int i, int j, WViewPlane &viewPlane, int aliasingLevel, WPath *path)
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
		WVector3 hitPoint;

		for (int j = 0; j < objects.size(); j++) {

			result = objects[j]->Intersection(ray, distance, shadingInfo);
			if (result > 0 && distance < bestDistance && distance > 0.001) {
				bestDistance = distance;
				normal = shadingInfo.normal;
				material = shadingInfo.material;
				localHitPoint = shadingInfo.localHitPoint;
				hitPoint = ray.origin + (ray.direction * bestDistance);
				anythingForThisPixelFound = true;
			}
		}

		if (anythingForThisPixelFound) {
			if (usePathTracing) {
				WColor *pathColor = new WColor(0.0); //loop this
				bool pathIsValid = intersectSinglePathRay(ray, shadingInfo, i, j, viewPlane, path, pathColor);
				if (!pathIsValid) {
					pixelColor = *pathColor;
				}
				else {
					pixelColor = *pathColor;
				}
			}
			else {
				shadingInfo.t = bestDistance;
				shadingInfo.material = material;
				shadingInfo.normal = normal;
				shadingInfo.localHitPoint = localHitPoint;
				shadingInfo.hitPoint = hitPoint;
				shadingInfo.hitObject = true;
				pixelColor = shadingInfo.material->shade(shadingInfo);

				//pixelColor = static_cast<WMatteMaterial*>(shadingInfo.material)->getCd();
			}
		}
		else {
			pixelColor = getBackgroundCheckers(i, j, viewPlane.getWidth(), viewPlane.getHeight());
			shadingInfo.hitObject = false;
		}

	}
	else {
		float offset = (float)(viewPlane.getPixelSize() * pow(0.5f, aliasingLevel+1));

		WRay topLeftRay		= generateSingleRay(ray, -	offset,		offset, i, j);
		WRay topRightRay	= generateSingleRay(ray,	offset,		offset, i, j);
		WRay bottomLeftRay	= generateSingleRay(ray, -	offset, -	offset, i, j);
		WRay bottomRightRay = generateSingleRay(ray,	offset, -	offset, i, j);

		WColor middle		= intersectSingleRay(ray,				shadingInfo, i, j, viewPlane, this->aliasingLevel, path);
		WColor topLeft		= intersectSingleRay(topLeftRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel, path);
		WColor topRight		= intersectSingleRay(topRightRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel, path);
		WColor bottomLeft	= intersectSingleRay(bottomLeftRay,		shadingInfo, i, j, viewPlane, this->aliasingLevel, path);
		WColor bottomRight	= intersectSingleRay(bottomRightRay,	shadingInfo, i, j, viewPlane, this->aliasingLevel, path);

		offset = (float)(viewPlane.getPixelSize() * pow(0.5f, aliasingLevel + 2)); //TODO: offset/2

		if (middle != topLeft) {
			intersectSingleRay(topLeftRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1, path);
			topLeftRay = generateSingleRay(ray, -offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(topRightRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1, path);
			topRightRay = generateSingleRay(ray, offset, offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomLeftRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1, path);
			bottomLeftRay = generateSingleRay(ray, -offset, -offset, i, j);
		}
		if (middle != topLeft) {
			intersectSingleRay(bottomRightRay, shadingInfo, i, j, viewPlane, aliasingLevel + 1, path);
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

WColor WCamera::intersectSingleReflectionRay(WRay & ray, WShadingInfo & shadingInfo, int i, int j, int aliasingLevel)
{	
	if (shadingInfo.rayBounces > 6) {
		return WColor(0.0f);
	}

	shadingInfo.rayBounces++;
	WShadingInfo ws(shadingInfo);
	WColor pixelColor;
	pixelColor = intersectSingleRay(ray, ws, 0, 0, (*viewPlane), aliasingLevel, NULL);
	if (ws.hitObject) {
		ws.ray = ray;
		pixelColor = ws.material->shade(ws);
	}
	else {
		pixelColor = getBackgroundCheckers(i, j, viewPlane->getWidth(), viewPlane->getHeight());
	}

	return pixelColor;
}

bool WCamera::intersectSinglePathRay(WRay & ray, WShadingInfo & shadingInfo, int i, int j, WViewPlane &viewPlane, WPath * path, WColor *color)
{	
	if(path->pathLength > pathTracingPathLength) {
		//check if the item hit is a light source
		//if not, return false
		//intersect with all lights, if lightHit == false
		if (path->pathLength > 0) {
			*color = *color / path->pathLength;
		}
		return true;
	}

	usePathTracing = false;
	WColor result = intersectSingleRay(ray, shadingInfo, i, j, viewPlane, 0, path);
	usePathTracing = true;
	if (!shadingInfo.hitObject) {
		if (path->pathLength > 0) {
			*color = *color / path->pathLength;
			return false;
		}
	}
	if (path->pathLength == 0) {
		*color = result;
	}
	//*color = *color + result;

	if (path != NULL) {
		path->rays.push_back(ray);
		path->pathLength++;
	}

	WRay randomRay = generateSinglePathBounceRay(ray, 0, 0, i, j, shadingInfo.hitPoint);
	return intersectSinglePathRay(randomRay, shadingInfo, i, j, viewPlane, path, color);
	
}

void WCamera::setUsePathTracing(bool use)
{	
	usePathTracing = use;
}

WCamera::WCamera(std::string name, WWorld &wr) : world(wr), viewPlane(new WViewPlane)
{
	this->name = name;
	aliasingLevel = 0;
	usePathTracing = false;
	pathTracingPathLength = 1;
}


WCamera::~WCamera()
{
}
