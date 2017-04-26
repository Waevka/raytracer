#pragma once
#include "WPhong.h"
class WMirror :
	public WPhong
{
public:
	WMirror();
	~WMirror();
	virtual WColor shade(WShadingInfo &si);
};

