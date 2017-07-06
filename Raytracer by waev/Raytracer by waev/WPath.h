#pragma once
#include "WRay.h"
#include <vector>
class WPath
{
public:
	std::vector<WRay> rays;
	int pathLength;
	WPath();
	~WPath();
};

