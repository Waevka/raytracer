#include "WImage.h"



WImage::WImage(int width, int height)
{	
	this->width = width;
	this->height = height;

	this->image = new WColor**[width];
	for (int i = 0; i < width; i++) {
		this->image[i] = new WColor*[height];
		for (int j = 0; j < height; j++) {
			this->image[i][j] = new WColor();
		}
	}
}

WImage::WImage()
{
	this->width = 100;
	this->height = 100;

	this->image = new WColor**[width];
	for (int i = 0; i < width; i++) {
		this->image[i] = new WColor*[height];
		for (int j = 0; j < height; j++) {
			this->image[i][j] = new WColor();
		}
	}
}


WImage::~WImage()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete this->image[i][j];
		}
		delete[] this->image[i];
	}
}

void WImage::setPixel(WColor &c, int x, int y)
{
	this->image[x][y]->r = c.r;
	this->image[x][y]->g = c.g;
	this->image[x][y]->b = c.b;
	this->image[x][y]->a = c.a;
}

WColor WImage::getPixel(int x, int y)
{	
	return WColor(this->image[x][y]->r, this->image[x][y]->g, this->image[x][y]->b, this->image[x][y]->a);
}

int WImage::getWidth()
{
	return width;
}

int WImage::getHeight()
{
	return height;
}
