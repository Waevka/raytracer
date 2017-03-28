#include <iostream>
#include <list>
#include "WWorld.h"
#include "WUtilities.h"
#include "WVector2.h"
#include "WVector3.h"
#include "WSphere.h"
#include "WRay.h"
#include "WPlane.h"
#include "WColor.h"
#include "WImage.h"

#define TESTSIZE 200


WWorld::WWorld()
{	
	viewPlane = WViewPlane(0.5f, TESTSIZE, TESTSIZE);
	backgroundColor = WColor(0.1f, 0.1f, 0.1f, 1.0f);
	///////////////
	WColor sphereColor(0.9f, 0.5f, 0.5f);

	WSphere *testSphere = new WSphere(WVector3(0, 0, 0), 10, sphereColor);
	WRay testRay(WVector3(0, 0, -20), WVector3(0, 0, 1));
	WRay testRay2(WVector3(0, 0, -20), WVector3(0, 1, 0));
	WRay testRay3(WVector3(0, -10, -10), WVector3(0, 1, 0));
	WPlane testPlane(WVector3(0.0f, 1.0f, 1.0f), 0.0f);
	WRay testPlaneRay1(WVector3(0, 10, 15), WVector3(0.0f, 1, 1)); // prostopadly
	WRay testPlaneRay2(WVector3(0, 10, 15), WVector3(0.0f, -1, 1)); // r�wnolegly

	float distance = 250.0f;
	std::cout << testSphere->toString() << "\n";
	std::cout << "TestSphere vs testRay1 (Should be: 2 intersections), result: " << testSphere->Intersection(testRay, distance) << "\n";
	WVector3 intersectionPoint = calculateIntersectionPoint(distance, testRay);
	std::cout << "Point of intersection:  " << intersectionPoint.toString() << "\n\n";
	distance = 250.0f;
	std::cout << "TestSphere vs testRay2 (Should be: 0 intersections), result: " << testSphere->Intersection(testRay2, distance) << "\n\n";
	distance = 250.0f;
	std::cout << "TestSphere vs testRay3 (Should be: 1 intersection), result: " << testSphere->Intersection(testRay3, distance) << "\n";
	WVector3 intersectionPoint3 = calculateIntersectionPoint(distance, testRay3);
	std::cout << "Point of intersection:  " << intersectionPoint3.toString() << "\n\n";
	distance = 25000.0f;
	std::cout << "TestPlane vs testPlaneRay1 (should be: 1 (from front)), result: " << testPlane.Intersection(testPlaneRay1, distance) << "\n";
	WVector3 intersectionPoint4 = calculateIntersectionPoint(distance, testPlaneRay1);
	std::cout << "Point of intersection:  " << intersectionPoint4.toString() << "\n\n"; 
	distance = 25000.0f;
	std::cout << "TestPlane vs testPlaneRay2 (should be: 0 (none)), result: " << testPlane.Intersection(testPlaneRay2, distance) << "\n";
	WVector3 intersectionPoint5 = calculateIntersectionPoint(distance, testPlaneRay2);
	//cout << "Point of intersection:  " << intersectionPoint5.toString() << "\n\n";
	//test = test.reflect(norm);
	//cout << test.toString();
	////////////////////////////////////////////////////////////////////////////////
	addObject(testSphere);
}


WWorld::~WWorld()
{
}

void WWorld::draw()
{	
	float distance;
	int result;
	WImage testImage(TESTSIZE, TESTSIZE);

	//base ray for viewPlane
	WRay testRay(WVector3(-20, -20, -20), WVector3(0, 0, 1));

	//generate rays
	WRay **testRays = new WRay*[viewPlane.getWidth()];
	for (int i = 0; i < viewPlane.getWidth(); i++) {
		testRays[i] = new WRay[viewPlane.getHeight()];
	}

	for (int i = 0; i < TESTSIZE; i++) {
		for (int j = 0; j < TESTSIZE; j++) {
			float newRayX = testRay.getOrigin().getX() + 0.2*i;
			float newRayY = testRay.getOrigin().getY() + 0.2*j;
			float newRayZ = testRay.getOrigin().getZ();
			testRays[i][j] = WRay(WVector3(newRayX, newRayY, newRayZ), testRay.getDirection());
		}
	}

	//check all rays with objects
	for (std::list<WGeometricObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		distance = 250.0f;
		for (int i = 0; i < TESTSIZE; i++) {
			for (int j = 0; j < TESTSIZE; j++) {
				result = (*iter)->Intersection(testRays[i][j], distance);
				if (result > 1) {
					testImage.setPixel((*iter)->getColor(), i, j);
				}
				else {
					testImage.setPixel(backgroundColor, i, j);
				}
			}
		}
	}

	/*
	//save result to file
	WColor testColor(0.5f, 0.7f, 0.5f);
	//imageWriter.writeImage(testColor, testWidth, testHeight);
	for (int i = 0; i < TESTSIZE; i++) {
		for (int j = 0; j < TESTSIZE; j++) {
			testImage.setPixel(WColor(0.0f + i*0.01f, 0.0f + j*0.01f, 1.0f), i, j);
		}
	}*/
	imageWriter.writeImage(testImage, TESTSIZE, TESTSIZE);
}

void WWorld::addObject(WGeometricObject* o)
{
	objects.push_back(o);
}
