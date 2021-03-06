#pragma once
#include "WColor.h"
#include "WShadingInfo.h"

class WMaterial
{
public:
	WMaterial();
	~WMaterial();
	virtual WColor shade(WShadingInfo &si);
	virtual WColor areaLightShade(WShadingInfo &si);
	virtual WColor pathShade(WShadingInfo &si);

};

