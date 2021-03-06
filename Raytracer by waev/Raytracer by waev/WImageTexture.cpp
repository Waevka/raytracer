#include "WImageTexture.h"
#include "WShadingInfo.h"
#include "WSphericalMap.h"
#define PI			3.1415926535897932384;
#define TWO_PI		6.2831853071795864769;
#define PI_ON_180	0.0174532925199432957;
#define invPI		0.3183098861837906715;
#define invTWO_PI	0.1591549430918953358;


WImageTexture::WImageTexture() : WTexture(), mapping_ptr(NULL), vres(), hres()
{
}

WImageTexture::WImageTexture(WMapping *map, int v, int h) : mapping_ptr(map), vres(v), hres(h)
{
}


WImageTexture::~WImageTexture()
{
}

void WImageTexture::setColor(WImage *c)
{
	image_ptr = c;
}

WColor WImageTexture::getColor(WShadingInfo & si) const
{
	int row, column;

	if (mapping_ptr) {
		mapping_ptr->getTexelCoordinates(si.localHitPoint, hres, vres,
			row, column);
	}
	else {
		row = (int)(si.v * (vres - 1));
		column = (int)(si.u * (hres - 1));
	}
	return(image_ptr->getPixel(column, row));
}
