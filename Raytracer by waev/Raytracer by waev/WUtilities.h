#pragma once
#include "WRay.h"
#include "WColor.h"

WVector3 calculateIntersectionPoint(float distance, WRay r);

WColor getBackgroundCheckers(int x, int y, int width, int height);

WColor randomColor();

WColor correctColor(WColor c);

inline float max(float x0, float x1);

WColor maxColorToOne(const WColor &c);

WColor clampColor(const WColor &c);
