//#include <stdio.h>
//#include "Vec2f.h"
//
///*Vec2f::Vec2f(void) // Replaced by having default values for the below constructor (0,0,0,1)
//{
//}*/
//
//Vec2f::Vec2f(float _x, float _y)
//:x(_x),y(_y)
//{
//}
///*
//Vec2f::Vec2f(const Vec2f &rhs)
//:x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w)
//{
//}
//*/
//Vec2f::~Vec2f(void)
//{
//}
//
//Vec2f & Vec2f::operator +=(const Vec2f &rhs)
//{
//	x += rhs.x;
//	y += rhs.y;
//
//	return *this;
//}
//
//Vec2f & Vec2f::operator -=(const Vec2f &rhs)
//{
//	x -= rhs.x;
//	y -= rhs.y;
//
//	return *this;
//}
//
//Vec2f Vec2f::operator +(const Vec2f &rhs)
//{
//    Vec2f v;
//	v.x = x + rhs.x;
//	v.y = y + rhs.y;
//
//	return v;
//}
//
//Vec2f Vec2f::operator -(const Vec2f &rhs)
//{
//	Vec2f v;
//	v.x = x - rhs.x;
//	v.y = y - rhs.y;
//
//	return v;
//}
//
//float Vec2f::Dot(const Vec2f &rhs) const
//{
//	return (x * rhs.x + y * rhs.y);
//}
//
//
//Vec2f & Vec2f::operator *=(const float s)
//{
//	x *= s;
//	y *= s;
//
//	return *this;
//}
//
//Vec2f & Vec2f::operator /=(const float s)
//{
//	x /= s;
//	y /= s;
//
//	return *this;
//}
//
//Vec2f Vec2f::operator *(const float s)
//{
//	Vec2f v;
//	v.x = x * s;
//	v.y = y * s;
//
//	return v;
//}
//
//Vec2f Vec2f::operator /(const float s)
//{
//    Vec2f v;
//	v.x = x / s;
//	v.y = y / s;
//
//	return v;
//}
//
//float Vec2f::Length() const
//{
//	return sqrtf(x * x + y * y );
//}
//
//float Vec2f::LengthSqr() const
//{
//	return (x * x + y * y);
//}
//
//
//bool Vec2f::operator ==(const Vec2f & rhs) const
//{
//	return ((x == rhs.x) && (y == rhs.y));
//}
//void Vec2f::operator=(const float & rhs)
//{
//	x = rhs;
//	y = rhs;
//}
//void Vec2f::Normalise()
//{
//    *this /= this->Length();
//}
//
//Vec2f Vec2f::getNormalised()
//{
//	return (*this / this->Length());
//}
//void Vec2f::DumpVec2f(char * s)
//{
//	if(s != NULL)printf("\n%f %f %s\n\n", x, y, s);
//	else printf("\n%f %f\n\n", x, y);
//}
