#pragma once
#include <string>
#include <math.h>
class WVector3
{
private:
public:
	float x;
	float y;
	float z;
	WVector3();
	WVector3(float xyz);
	WVector3(float x, float y, float z);
	WVector3(const WVector3 &v);
	WVector3(const WVector3 &v1, const WVector3 &v2);
	~WVector3();

	std::string toString();
	float getLength();
	float getLengthSquared();
	void divide(float n);
	void negate();
	void add(WVector3 &v);
	void subtract(WVector3 &v);
	void mag(float f);
	void normalize();
	WVector3 normalizeProduct();
	float dot(WVector3 &v);
	float dot(const WVector3 &v) const;
	WVector3 cross(WVector3 &v);
	WVector3 reflect(WVector3 &normal);
	WVector3 magProduct(WVector3 &v, float f);
	WVector3 toPoint();
	WVector3 lerp(WVector3 &v, float t);
	WVector3 hat();
	float distance(WVector3 &v);

	//operators
	WVector3 operator* (float f);
	WVector3 operator* (const float &f) const;
	WVector3 operator* (WVector3 &v);
	WVector3 operator* (const WVector3 &v) const;
	WVector3 operator+ (WVector3 &v); 
	WVector3 operator+ (float v);
	WVector3 operator- (WVector3 &v);
	WVector3 operator- ();
	WVector3 operator- () const;
	bool operator== (WVector3 &v);
	bool operator!= (WVector3 &v);
	WVector3 operator/ (float f);
};

