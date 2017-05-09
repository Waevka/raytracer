#pragma once
#include "WModel.h"
class WTrianglePlane :
	public WModel
{
public:
	WTrianglePlane(WVector3 &center, float width, float height, int direction); // normal direction, 0 - up, 1 - down, 2 - left, 3 - right, 4 - to camera
	~WTrianglePlane();
	virtual int Intersection(WRay &ray, float &dist, WShadingInfo &ws);
private:
	WVector3 center;
	float width;
	float height;
	int direction;

	void createUpPlane();
	void createDownPlane();
	void createLeftPlane();
	void createRightPlane();
	void createFrontPlane();
	void createBackPlane();
};

