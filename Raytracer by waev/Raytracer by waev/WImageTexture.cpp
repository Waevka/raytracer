#include "WImageTexture.h"



WImageTexture::WImageTexture() : mapping_ptr(NULL)
{
}


WImageTexture::~WImageTexture()
{
}

WColor WImageTexture::getColor(const WShadingInfo & si) const
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
	return(image_ptr->getPixel(row, column));
}
