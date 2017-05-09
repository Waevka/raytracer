#pragma once
#include "WPhong.h"
#include "WTransparentBDTF.h"
#include "WMirrorBRDF.h"

class WTransparentMaterial :
	public WPhong
{
private:
	WTransparentBDTF *transparent;
	WMirrorBRDF *mirror;
public:
	WTransparentMaterial();
	~WTransparentMaterial();
	void setKr(float f);
	void setIor(float i); 
	void setKt(float k);
	virtual WColor shade(WShadingInfo &si);
};

