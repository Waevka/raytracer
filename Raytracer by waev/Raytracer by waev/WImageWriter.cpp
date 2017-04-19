#include "WImageWriter.h"
#include "Image.h"
#include "WImage.h"


WImageWriter::WImageWriter()
{
}


WImageWriter::~WImageWriter()
{
}

void WImageWriter::writeImage(WImage &i, int width, int height, string filename)
{
	short w = (short)width;
	short h = (short)height;

	TGAImage *img = new TGAImage(h, w); // careful here - swapped coords!

	for (int x = 0; x<w; x++)
		for (int y = 0; y<h; y++)
		{	
			WColor c = i.getPixel(x,y);
			Colour cc;
			cc.r = (unsigned char)floor(c.r == 1.0f ? 255 : c.r * 256.0f);
			cc.g = (unsigned char)floor(c.g == 1.0f ? 255 : c.g * 256.0f);
			cc.b = (unsigned char)floor(c.b == 1.0f ? 255 : c.b * 256.0f);
			cc.a = (unsigned char)floor(c.a == 1.0f ? 255 : c.a * 256.0f);
			img->setPixel(cc, x, y); 
		}

	//write the image to disk
	img->WriteImage(filename);

	delete img;
}

WImage* WImageWriter::readImage(int width, int height, std::string filename)
{	
	char fn[256];
	TGAFILE *tgaFile = new TGAFILE();
	unsigned char ucharBad;

	short int sintBad;
	long imageSize;
	int colorMode;
	unsigned char colorSwap;

	FILE *filePtr;
	fopen_s(&filePtr, filename.c_str(), "rb");
	if (filePtr == NULL)
	{
		std::cout << "texture error";
	}

	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);
	if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
	{
		fclose(filePtr);
		std::cout << "texture error";
	}

	// Read 13 bytes of data we don't need.
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// Read the image's width and height.
	fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

	// Read the bit depth.
	fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

	// Read one byte of data we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// Color mode -> 3 = BGR, 4 = BGRA.
	colorMode = tgaFile->bitCount / 8;
	imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

	// Allocate memory for the image data.
	tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);
	WImage *i = new WImage((int)tgaFile->imageWidth, (int)tgaFile->imageHeight);

	// Read the image data.
	fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

	int x = 0;
	int y = 0;
	// Change from BGR to RGB so OpenGL can read the image data.
	for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{	
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx + 2] = colorSwap;

		float r = tgaFile->imageData[imageIdx] / 256.0f;
		float g = tgaFile->imageData[imageIdx + 1] / 256.0f;
		float b = tgaFile->imageData[imageIdx + 2] / 256.0f;
		//if (tgaFile->imageData[imageIdx] == 128)
			//std::cout << "fug:";
		WColor color(r, g, b);
		i->setPixel(color, x, y);
		if (x < (int)tgaFile->imageWidth) {
			x++;
		}
		if(x == (int) tgaFile->imageWidth) {
			x = 0;
			y += 1;
		}
	}


	fclose(filePtr);
	return i;
}
