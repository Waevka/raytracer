#pragma once
#include "WMaterial.h"
#include "WLambertian.h"
class WMatteMaterial :
	public WMaterial
{
public:
	WMatteMaterial();
	WMatteMaterial(const WMatteMaterial &m);
	~WMatteMaterial();
	virtual WColor shade(WShadingInfo &si);
	void setKa(float k);
	void setKd(float k);
	void setCd(WColor c);
	WColor getCd();
private:
	WLambertian *ambient;
	WLambertian *diffuse;
};

