#include "WImageTexture.h"
#include "WShadingInfo.h"
#include "WSphericalMap.h"
#define PI			3.1415926535897932384;
#define TWO_PI		6.2831853071795864769;
#define PI_ON_180	0.0174532925199432957;
#define invPI		0.3183098861837906715;
#define invTWO_PI	0.1591549430918953358;


WImageTexture::WImageTexture() : WTexture(), mapping_ptr(new WSphericalMap()), vres(600), hres(500)
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
	WVector3 lhp(si.localHitPoint);
	lhp.normalize();
	float theta = acos(lhp.y);
	float phi = atan2(lhp.x, lhp.z);
	if (phi < 0.0) {
		phi += TWO_PI;
	}

	// map to (u, v)
	si.u = phi * invTWO_PI;
	si.v = 1 - theta * invPI;

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
