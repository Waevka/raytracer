#pragma once
#include "WImage.h"
#include <string>

typedef struct
{
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
	unsigned char *imageData;
} TGAFILE;

class WImageWriter
{
public:
	WImageWriter();
	~WImageWriter();
	WImage* readImage(int width, int height, std::string filename);
	void writeImage(WImage &i, int width, int height, std::string filename);
};

