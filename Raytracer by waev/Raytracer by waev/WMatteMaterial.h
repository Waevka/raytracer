#pragma once
#include "WMaterial.h"
#include "WLambertian.h"
class WMatteMaterial :
	public WMaterial
{
public:
	WMatteMaterial();
	~WMatteMaterial();
	//virtual WColor shade(WShadingInfo si);
	void setKa(float k);
	void setKd(float k);
	void setCd(WColor c);
private:
	WLambertian *ambient;
	WLambertian *diffuse;
};

