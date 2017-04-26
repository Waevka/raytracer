#pragma once
#include "WPhong.h"
#include "WMirrorBRDF.h"
class WMirror :
	public WPhong
{
public:
	WMirror();
	~WMirror();
	virtual WColor shade(WShadingInfo &si);
	void setKr(float f);
	void setCr(WColor c);
private:
	WMirrorBRDF *mirror;
};

