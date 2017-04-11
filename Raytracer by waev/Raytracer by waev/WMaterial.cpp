#include "WMaterial.h"

WMaterial::WMaterial()
{
}


WMaterial::~WMaterial()
{
}

WColor WMaterial::shade(WShadingInfo &si)
{
	return si.color;
}

WColor WMaterial::areaLightShade(WShadingInfo & si)
{
	return si.color;
}

WColor WMaterial::pathShade(WShadingInfo & si)
{
	return si.color;
}
