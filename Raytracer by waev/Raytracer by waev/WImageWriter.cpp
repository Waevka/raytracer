#include "WImageWriter.h"
#include "Image.h"


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
