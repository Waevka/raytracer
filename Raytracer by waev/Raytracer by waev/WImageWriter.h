#pragma once
#include "WImage.h"
#include <string>

class WImageWriter
{
public:
	WImageWriter();
	~WImageWriter();
	void writeImage(WImage &i, int width, int height, std::string filename);
};

