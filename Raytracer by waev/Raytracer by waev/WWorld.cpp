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
#include "WGlossySpecular.h"
#include "WSphericalMap.h"
#include "WImageTexture.h"
#include "WPhong.h"
#include "WTrianglePlane.h"
#include "WRectangleMap.h"
#include "WMirror.h"
#include "WTransparentMaterial.h"

#define TESTSIZE_W 500
#define TESTSIZE_H 600


WWorld::WWorld()
{	
	backgroundColor = WColor(0.1f, 0.1f, 0.1f, 1.0f);
	ambient = new WAmbient();
	/////////////// Lights

	WPointLight *pointlight1 = new WPointLight();
	pointlight1->setLocation(WVector3(28, -13, 15));
	pointlight1->scaleRadiance(3.0f);
	pointlight1->setColor(WColor(0.9f, 0.9f, 0.7f));
	addLight(pointlight1);

	WPointLight *pointlight2 = new WPointLight();
	pointlight2->setLocation(WVector3(20, 5, 15));
	pointlight2->scaleRadiance(2.0f);
	pointlight2->setColor(WColor(0.6f, 0.5f, 0.6f));
	addLight(pointlight2);

	///////////////
	WColor sphereColor(1.0f, 0.0f, 0.0f);
	WColor sphereColor2(0.0f, 1.0f, 0.0f);
	WColor sphereColor3(0.2f, 0.4f, 0.8f);
	WColor sphereColor4(0.2f, 0.4f, 0.8f);

	WSphere *testSphere = new WSphere(WVector3(-3, 0.5, -0.5), 6, sphereColor); //textured
	WSphere *testSphere2 = new WSphere(WVector3(14, -24, 3), 5, sphereColor2); //red
	WSphere *testSphere3 = new WSphere(WVector3(14, -12.0, 2.5), 6, sphereColor3); //mirror
	WSphere *testSphere4 = new WSphere(WVector3(14, -16.0, 8.5), 4, sphereColor4); //transparent

	WModel *testSphereModel = new WModel();
	testSphereModel->name = "SPHERE";
	testSphereModel->addObject(testSphere);

	WModel *testSphereModel2 = new WModel();
	testSphereModel2->name = "SPHERE2";
	testSphereModel2-> addObject(testSphere2);

	WModel *testSphereModel3 = new WModel();
	testSphereModel3->name = "SPHERE3";
	testSphereModel3->addObject(testSphere3);

	WModel *testSphereModel4 = new WModel();
	testSphereModel4->name = "SPHERE4";
	testSphereModel4->addObject(testSphere4);

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
	triangleMat->setCd(WColor(0.2f,0.1f,0.8f));
	triangleMat->setExp(10);

	WSphericalMap* sphericalMapPtr = new WSphericalMap();
	WImage *texture1 = imageWriter.readImage(1, 1, "20minlol.tga");
	WImageTexture *imageTexture = new WImageTexture(sphericalMapPtr, texture1->getHeight(), texture1->getWidth());
	imageTexture->setColor(texture1);
	WSV_MatteMaterial *sphereMat = new WSV_MatteMaterial();
	sphereMat->setKa(0.25f);
	sphereMat->setKd(0.65f);
	sphereMat->setCd(imageTexture);

	WRectangleMap *rectangleMapPtr = new WRectangleMap();
	WImage *texture2 = imageWriter.readImage(1, 1, "buny.tga");
	WImageTexture *imagePlaneTexture = new WImageTexture(rectangleMapPtr, texture2->getHeight(), texture2->getWidth());
	imagePlaneTexture->setColor(texture2);
	WSV_MatteMaterial *planeMat = new WSV_MatteMaterial();
	planeMat->setKa(0.25f);
	planeMat->setKd(0.65f);
	planeMat->setCd(imagePlaneTexture);

	WPhong *sphere2Mat = new WPhong();
	sphere2Mat->setKa(0.25f);
	sphere2Mat->setKd(0.65f);
	sphere2Mat->setCd(WColor(1.0, 0.3f, 0.0f));
	sphere2Mat->setKs(0.2f);
	sphere2Mat->setExp(200);
	//sphereMat->setCd(WColor(1, 0.25f, 0));

	WMatteMaterial *whiteWallMaterial = new WMatteMaterial();
	whiteWallMaterial->setCd(WColor(1.0f, 1.0f, 1.0f));
	whiteWallMaterial->setKa(0.25f);
	whiteWallMaterial->setKd(0.65f);

	WMatteMaterial *redWallMaterial = new WMatteMaterial();
	redWallMaterial->setCd(WColor(1.0f, 0.3f, 0.0f));
	redWallMaterial->setKa(0.25f);
	redWallMaterial->setKd(0.65f);

	WMatteMaterial *greenWallMaterial = new WMatteMaterial();
	greenWallMaterial->setCd(WColor(0.0f, 1.0f, 0.0f));
	greenWallMaterial->setKa(0.25f);
	greenWallMaterial->setKd(0.65f);

	WMirror *sphere3Mat = new WMirror();
	sphere3Mat->setKa(1.0f);
	sphere3Mat->setKd(1.00f);
	sphere3Mat->setCd(WColor(1.0, 1.0, 1.0));
	sphere3Mat->setKs(1.0f);
	sphere3Mat->setExp(200);
	sphere3Mat->setKr(1.0f);
	sphere3Mat->setCr(WColor(1.0f, 1.0f, 1.0f));

	WTransparentMaterial *sphere4Mat = new WTransparentMaterial();
	sphere4Mat->setKa(1.0f);
	sphere4Mat->setKd(1.00f);
	sphere4Mat->setCd(WColor(1.0, 0.7, 0.7));
	sphere4Mat->setKs(1.0f);
	sphere4Mat->setExp(200);
	sphere4Mat->setKr(1.0f);
	sphere4Mat->setIor(1.01f);
	sphere4Mat->setKt(0.9);

	WPhong *monkeyMat = new WPhong();
	monkeyMat->setKa(0.25f);
	monkeyMat->setKd(0.65f);
	monkeyMat->setCd(WColor(0.5, 0.5, 1));
	monkeyMat->setKs(0.2f);
	monkeyMat->setExp(10);

	(*triangle).setMaterial(triangleMat);
	(*testSphere).setMaterial(sphereMat);
	(*testSphere2).setMaterial(sphere2Mat);
	(*testSphere3).setMaterial(sphere3Mat);
	(*testSphere4).setMaterial(sphere4Mat);
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
	imageWriter.writeImage(*texture1, 500, 600, "pupa.tga");

	/////////////////////////////////////////
	//testSphereModel->addObject(testSphere2);
	addObject(testSphereModel2);
	addObject(testSphereModel);
	addObject(testSphereModel3);
	addObject(testSphereModel4);
	//addObject(triangle);
	//addObject(planetr1);
	//addObject(planetr2);

	//std::vector<WTriangle*> readTriangles = objReader.readFile("cube.obj");
	WModel *monkey = new WModel();
	monkey->objects = objReader.readFile("monkeyx8.obj");
	monkey->name = "MONKEY";
	monkey->setMaterial(monkeyMat);
	//addObject(monkey);

	WTrianglePlane *flatPlaneBuny = new WTrianglePlane(WVector3(-25.0f, 0.0f, 0.0f), 50, 30, 0);
	//flatPlane->objects = objReader.readFile("blenderflat.obj");
	flatPlaneBuny->name = "FlatPlaneBuny";
	flatPlaneBuny->setMaterial(planeMat);
	addObject(flatPlaneBuny);

	float hBoxDelta = -10.0f; // horizontal
	float verticalBoxDelta = 8.0f; // vertical

	WTrianglePlane *flatPlane1 = new WTrianglePlane(WVector3(-10.0f, 0.0f + hBoxDelta, 0.0f + verticalBoxDelta), 50, 30, 0);
	flatPlane1->name = "FlatPlaneBottom";
	flatPlane1->setMaterial(whiteWallMaterial);
	addObject(flatPlane1);

	WTrianglePlane *flatPlane2 = new WTrianglePlane(WVector3(30.0f, 0.0f + hBoxDelta, 0.0f + verticalBoxDelta), 50, 30, 1);
	flatPlane2->name = "FlatPlaneTop";
	flatPlane2->setMaterial(whiteWallMaterial);
	addObject(flatPlane2);

	WTrianglePlane *flatPlane3 = new WTrianglePlane(WVector3(10.0f, 25.0f + hBoxDelta, 0.0f + verticalBoxDelta), 50, 30, 2);
	flatPlane3->name = "FlatPlaneRight";
	flatPlane3->setMaterial(greenWallMaterial);
	addObject(flatPlane3);

	WTrianglePlane *flatPlane4 = new WTrianglePlane(WVector3(10.0f, -25.0f + hBoxDelta, 0.0f + verticalBoxDelta), 50, 30, 3);
	flatPlane4->name = "FlatPlaneLeft";
	flatPlane4->setMaterial(redWallMaterial);
	addObject(flatPlane4);

	WTrianglePlane *flatPlane5 = new WTrianglePlane(WVector3(10.0f, 0.0f + hBoxDelta, -15.0f + verticalBoxDelta), 50, 50, 4);
	flatPlane5->name = "FlatPlaneFront";
	flatPlane5->setMaterial(whiteWallMaterial);
	addObject(flatPlane5);

	WTrianglePlane *flatPlane6 = new WTrianglePlane(WVector3(-15.0f, 0.0f + hBoxDelta, 30.0f + verticalBoxDelta), 100, 100, 5);
	flatPlane6->name = "FlatPlaneBack";
	flatPlane6->setMaterial(whiteWallMaterial);
	//addObject(flatPlane6);
}


WWorld::~WWorld()
{
}

void WWorld::draw()
{	
	WOrthoCamera ortho(*this);
	WPerspectiveCamera persp(*this);
	perspCam = &persp;

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

