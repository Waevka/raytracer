#pragma once
#include "WBRDF.h"
class WMirrorBRDF : public WBRDF
{
private:
	float kr;
	WColor cr;
public:
	WMirrorBRDF();
	~WMirrorBRDF();
	void setKr(float k);
	float getKr();
	void setCr(WColor c);
	WColor getCr();
	virtual WColor sample_f(const WShadingInfo &si, WVector3 &wi, const WVector3 &wo) const;
};

