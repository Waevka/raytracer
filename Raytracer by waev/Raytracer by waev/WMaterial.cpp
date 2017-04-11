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
