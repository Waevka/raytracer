#pragma once
#include "WMaterial.h"
#include "WTexture.h"
#include "WSV_Lambertian.h"
class WSV_MatteMaterial :
	public WMaterial
{
public:
	WSV_MatteMaterial();
	~WSV_MatteMaterial();
	virtual WColor shade(WShadingInfo &si);
	void setCd(WTexture* t_ptr);
	void setKa(float k);
	void setKd(float k);
private:
	WSV_Lambertian *diffuse;
	WSV_Lambertian *ambient;
};

