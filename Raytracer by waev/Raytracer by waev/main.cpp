#include <iostream>
#include "WVector2.h"
#include "WVector3.h"
#include "WSphere.h"
#include "WRay.h"

using namespace std;

WVector3 calculateIntersectionPoint(float distance, WRay r);

int main(int argc, char* argv[]) {
	cout << "Raytracer test" << endl;
	WSphere testSphere(WVector3(0, 0, 0), 10);
	WRay testRay(WVector3(0, 0, -20), WVector3(0, 0, 1));
	WRay testRay2(WVector3(0, 0, -20), WVector3(0, 1, 0));
	WRay testRay3(WVector3(0, -10, -10), WVector3(0, 1, 0));
	float distance = 250.0f;
	cout << testSphere.toString() << "\n";
	cout << "TestSphere vs testRay1 (Should be: 2 intersections), result: " << testSphere.Intersect(testRay, distance) << "\n";
	WVector3 intersectionPoint = calculateIntersectionPoint(distance, testRay);
	cout << "Point of intersection:  " << intersectionPoint.toString() << "\n\n";
	distance = 250.0f;
	cout << "TestSphere vs testRay2 (Should be: 0 intersections), result: " << testSphere.Intersect(testRay2, distance) << "\n\n";
	distance = 250.0f;
	cout << "TestSphere vs testRay3 (Should be: 1 intersection), result: " << testSphere.Intersect(testRay3, distance) << "\n";
	WVector3 intersectionPoint3 = calculateIntersectionPoint(distance, testRay3);
	cout << "Point of intersection:  " << intersectionPoint3.toString() << "\n\n";
	//test = test.reflect(norm);
	//cout << test.toString();
	cin.get();
	return 0;
}

WVector3 calculateIntersectionPoint(float distance, WRay r) {
	WVector3 result(r.getDirection());
	result = result * distance;
	return result;
}