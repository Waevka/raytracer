#pragma once
#include "WVector3.h"

class WSphere
{
private:
	WVector3 origin;
	float radius;
public:
	WSphere();
	WSphere(WVector3 v, float r);
	~WSphere();
};

