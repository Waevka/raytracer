#pragma once
#include "WMaterial.h"
#include "WLambertian.h"
#include "WGlossySpecular.h"

class WPhong :
	public WMaterial
{
public:
	WPhong();
	~WPhong();
	virtual WColor shade(WShadingInfo &si);
	void setKa(float k);
	void setKd(float k);
	void setKs(float k);
	void setCd(WColor c);
	void setExp(float f);
	WColor getCd();

protected:
	WLambertian *ambient;
	WLambertian *diffuse;
	WGlossySpecular *specular;
};

