#pragma once
#include <string>
#include <vector>
#include "WGeometricObject.h"
#include "WImageWriter.h"
#include "WShadingInfo.h"
#include "WViewPlane.h"
#include "WPath.h"
class WCamera
{
private:
protected:
	WImageWriter imageWriter;
	std::string name;
	WWorld &world;
	WViewPlane *viewPlane;
	bool usePathTracing;
public:
	virtual void draw(int TESTSIZE_W, int TESTSIZE_H, WViewPlane &viewPlane);
	virtual void generateRays(WRay** &rays, WViewPlane &viewPlane);
	virtual WRay generateSingleRay(WRay &ray, float xOffset, float yOffset, int i, int j) = 0;
	virtual WRay generateSinglePathBounceRay(WRay &ray, float xOffset, float yOffset, int i, int j, WVector3 hitPoint) = 0;
	virtual void intersectRays(WViewPlane &viewPlane, WRay** &rays, WImage &testImage);
	virtual WColor rayAliasing(int currentLevel);
	virtual WColor intersectSingleRay(WRay &ray, WShadingInfo &shadingInfo, int i, int j, WViewPlane &viewPlane, int aliasingLevel, WPath *path);
	virtual WColor intersectSingleReflectionRay(WRay &ray, WShadingInfo &shadingInfo, int i, int j, int aliasingLevel);
	bool intersectSinglePathRay(WRay &ray, WShadingInfo &shadingInfo, int i, int j, WViewPlane &viewPlane, WPath *path, WColor *color);
	void setUsePathTracing(bool use);
	WCamera(std::string name, WWorld &wr);
	~WCamera();
	int aliasingLevel;
	int pathTracingPathLength;
};

