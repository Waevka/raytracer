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
#include "WOrthoCamera.h"
#include "WPerspectiveCamera.h"

#define TESTSIZE_W 500
#define TESTSIZE_H 600


WWorld::WWorld()
{	
	viewPlane = WViewPlane(0.5f, TESTSIZE_W, TESTSIZE_H);
	viewPlane.setPixelSize(0.05f);
	backgroundColor = WColor(0.1f, 0.1f, 0.1f, 1.0f);
	///////////////
	WColor sphereColor(0.9f, 0.5f, 0.5f);
	WColor sphereColor2(0.4f, 0.8f, 0.2f);

	WSphere *testSphere = new WSphere(WVector3(0, 0, 0), 10, sphereColor);
	WSphere *testSphere2 = new WSphere(WVector3(-15, 2, 10), 12, sphereColor2);
	WRay testRay(WVector3(0, 0, -20), WVector3(0, 0, 1));
	WRay testRay2(WVector3(0, 0, -20), WVector3(0, 1, 0));
	WRay testRay3(WVector3(0, -10, -10), WVector3(0, 1, 0));
	WPlane testPlane(WVector3(0.0f, 1.0f, 1.0f), 0.0f);
	WRay testPlaneRay1(WVector3(0, 10, 15), WVector3(0.0f, 1, 1)); // prostopadly
	WRay testPlaneRay2(WVector3(0, 10, 15), WVector3(0.0f, -1, 1)); // równolegly

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
	addObject(testSphere2);

}


WWorld::~WWorld()
{
}

void WWorld::draw()
{	
	WOrthoCamera ortho;
	WPerspectiveCamera persp;

	ortho.draw(TESTSIZE_W, TESTSIZE_H, objects);
}

void WWorld::addObject(WGeometricObject* o)
{
	objects.push_back(o);
}

void WWorld::addCamera(WCamera * c)
{
	cameras.push_back(c);
}

