#include <stdio.h>
#include "Vec3f.h"

Vec3f::Vec3f(float _x, float _y, float _z)
:x(_x),y(_y),z(_z)
{
}
/*
Vec3f::Vec3f(const Vec3f &rhs)
:x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w)
{
}
*/
Vec3f::~Vec3f(void)
{
}

Vec3f & Vec3f::operator +=(const Vec3f &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vec3f & Vec3f::operator -=(const Vec3f &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

float Vec3f::Dot3(const Vec3f &rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vec3f Vec3f::Cross(const Vec3f &rhs) const
{
	return Vec3f(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

Vec3f & Vec3f::operator *=(const float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vec3f & Vec3f::operator /=(const float s)
{
	x /= s;
	y /= s;
	z /= s;

	return *this;
}

float Vec3f::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vec3f::LengthSqr() const
{
	return (x * x + y * y + z * z);
}


bool Vec3f::operator ==(const Vec3f & rhs) const
{
	return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
}
void Vec3f::operator=(const float & rhs)
{
	x = rhs;
	y = rhs;
	z = rhs;
}
Vec3f Vec3f::Normalise()
{
	return (*this / this->Length());
}

void Vec3f::NormaliseSelf()
{
	*this /= this->Length();
}
void Vec3f::DumpVec3f(char * s)
{
	if(s != NULL)printf("\n%f %f %f %s\n\n", x, y, z, s);
	else printf("\n%f %f %f\n\n", x, y, z);
}
