#pragma once
#include "WImage.h"

class WImageWriter
{
public:
	WImageWriter();
	~WImageWriter();
	void writeImage(WImage &i, int width, int height);
};

