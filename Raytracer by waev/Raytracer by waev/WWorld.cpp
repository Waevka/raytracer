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
#include "WTriangle.h"
#include "WObjReader.h"
#include "WAmbient.h"
#include "WMatteMaterial.h"
#include "WPerspectiveCamera.h"
#include "WPointLight.h"
#include "WSV_MatteMaterial.h"
#include "WMatteMaterial.h"
#include "WModel.h"
#include "WPhong.h"

#define TESTSIZE_W 500
#define TESTSIZE_H 600


WWorld::WWorld()
{	
	backgroundColor = WColor(0.1f, 0.1f, 0.1f, 1.0f);
	ambient = new WAmbient();
	/////////////// Lights

	WPointLight *pointlight1 = new WPointLight();
	pointlight1->setLocation(WVector3(12,-9.5,5.5f));
	pointlight1->scaleRadiance(3.0f);
	pointlight1->setColor(WColor(1.0f, 0.0, 0.0));
	addLight(pointlight1);

	WPointLight *pointlight2 = new WPointLight();
	pointlight2->setLocation(WVector3(10, -20.5, 9.5f));
	pointlight2->scaleRadiance(3.0f);
	pointlight2->setColor(WColor(0.2f, 0.2f, 1.0f));
	addLight(pointlight2);

	///////////////
	WColor sphereColor(0.9f, 0.5f, 0.5f);
	WColor sphereColor2(0.4f, 0.8f, 0.2f);
	WColor sphereColor3(0.2f, 0.4f, 0.8f);

	WSphere *testSphere = new WSphere(WVector3(-3, 0.5, -0.5), 6, sphereColor);
	WSphere *testSphere2 = new WSphere(WVector3(6, -8, 0), 5, sphereColor2);
	WSphere *testSphere3 = new WSphere(WVector3(4, -8, -4), 6, sphereColor3);

	WModel *testSphereModel = new WModel();
	testSphereModel->name = "SPHERE";
	testSphereModel->addObject(testSphere);

	WModel *testSphereModel2 = new WModel();
	testSphereModel2->name = "SPHERE2";
	testSphereModel2-> addObject(testSphere2);

	WTriangle *triangle= new WTriangle(
		WVector3(-10,-10,0),
		WVector3(25,10,10),
		WVector3(-50,0,10)
		);
	(*triangle).normal = WVector3(0, 1, 0);

	//// plane
	WTriangle *planetr1 = new WTriangle(
		WVector3(0, -40, -40),
		WVector3(0, -40, 15),
		WVector3(0, 30, 15));
	(*planetr1).normal = WVector3(1, 0, 0);

	WTriangle *planetr2 = new WTriangle(
		WVector3(0, -40, -40),
		WVector3(0, 25, -40),
		WVector3(0, 25, 15));
	(*planetr2).normal = WVector3(1, 0, 0);
	////

	WPhong *triangleMat = new WPhong();
	triangleMat->setKa(0.25f);
	triangleMat->setKd(0.65f);
	triangleMat->setKs(0.2f);
	triangleMat->setCd(WColor(1,1,0));
	triangleMat->setExp(10);
	WSV_MatteMaterial *sphereMat = new WSV_MatteMaterial();
	sphereMat->setKa(0.25f);
	sphereMat->setKd(0.65f);
	//sphereMat->setKs(0.2f);
	//sphereMat->setExp(200);
	//sphereMat->setCd(WColor(1, 0.25f, 0));
	WPhong *monkeyMat = new WPhong();
	monkeyMat->setKa(0.25f);
	monkeyMat->setKd(0.65f);
	monkeyMat->setCd(WColor(0.5, 0.5, 1));
	monkeyMat->setKs(0.2f);
	monkeyMat->setExp(10);

	(*triangle).setMaterial(triangleMat);
	(*testSphere).setMaterial(triangleMat);
	(*testSphere2).setMaterial(sphereMat);
	(*planetr1).setMaterial(triangleMat);
	(*planetr2).setMaterial(triangleMat);

	WRay testRay(WVector3(0, 0, -20), WVector3(0, 0, 1));
	WRay testRay2(WVector3(0, 0, -20), WVector3(0, 1, 0));
	WRay testRay3(WVector3(0, -10, -10), WVector3(0, 1, 0));
	WPlane testPlane(WVector3(0.0f, 1.0f, 1.0f), 0.0f);
	WRay testPlaneRay1(WVector3(0, 10, 15), WVector3(0.0f, 1, 1)); // prostopadly
	WRay testPlaneRay2(WVector3(0, 10, 15), WVector3(0.0f, -1, 1)); // równolegly

	float distance = 250.0f; /*
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
	*/
	/////////////////////////////////////////TEXTURES///////////////////////////////////////

	WImage *texture1 = imageWriter.readImage(1, 1, "20minlol.tga");
	imageWriter.writeImage(*texture1, 500, 600, "pupa.tga");

	/////////////////////////////////////////
	//testSphereModel->addObject(testSphere2);
	addObject(testSphereModel2);
	addObject(testSphereModel);
	//addObject(triangle);
	//addObject(planetr1);
	//addObject(planetr2);

	//std::vector<WTriangle*> readTriangles = objReader.readFile("cube.obj");
	WModel *monkey = new WModel();
	monkey->objects = objReader.readFile("monkeyx8.obj");
	monkey->name = "MONKEY";
	monkey->setMaterial(monkeyMat);
	//monkey->addObject(testSphere2);
	//monkey->addObject(testSphere);
	//addObject(monkey);
	//addObject(testSphereModel);
	//for (int i = 0; i < readTriangles.size(); i++) {
	//	readTriangles[i]->setMaterial(triangleMat);
		//addObject(readTriangles[i]);
	//}
	WModel *flatPlane = new WModel();
	flatPlane->objects = objReader.readFile("blenderflat.obj");
	flatPlane->name = "FlatPlane";
	flatPlane->setMaterial(triangleMat);
	//addObject(flatPlane);


}


WWorld::~WWorld()
{
}

void WWorld::draw()
{	
	WOrthoCamera ortho(*this);
	WPerspectiveCamera persp(*this);

	//ortho - draw 
	/*
	WRay rayOrtho(WVector3(0, 0, -20), WVector3(0, 0, 1));
	WViewPlane viewPlaneOrtho = WViewPlane(0.05f, TESTSIZE_W, TESTSIZE_H, rayOrtho);
	ortho.draw(TESTSIZE_W, TESTSIZE_H, objects, viewPlaneOrtho);*/

	//persp - draw
	WRay rayPersp(WVector3(10, -10, 30), WVector3(0.5f, 0.0f, -1.0f));
	WViewPlane viewPlanePersp = WViewPlane(0.05f, TESTSIZE_W, TESTSIZE_H, rayPersp);
	persp.setDistance(-10);
	persp.draw(TESTSIZE_W, TESTSIZE_H, viewPlanePersp);
}

void WWorld::addObject(WGeometricObject* o)
{
	objects.push_back(o);
}

void WWorld::addCamera(WCamera * c)
{
	cameras.push_back(c);
}

void WWorld::addLight(WLight * l)
{	
	lights.push_back(l);
}

