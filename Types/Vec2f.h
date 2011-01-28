#ifndef VEC2F_H
#define VEC2F_H

#include <math.h>

struct Vec2f { //Simple vector class
	float x;
	float y;

	Vec2f( float pX = 0.0f, float pY = 0.0f ) : x( pX ), y( pY ) { }

	~Vec2f() { }

	Vec2f operator*( float s ) { return Vec2f( x*s, y*s ); }
	Vec2f operator/( float s ) { return Vec2f( x/s, y/s ); }
	Vec2f operator+( Vec2f B ) { return Vec2f( x + B.x, y + B.y ); }
	Vec2f operator-( Vec2f B ) { return Vec2f( x - B.x, y - B.y ); }
	Vec2f operator-() { return Vec2f( -x, -y ); }
	float operator*( Vec2f B ) { return x*B.x + y*B.y; }
	void operator=( Vec2f B ) { x = B.x; y = B.y; }
	void operator+=( Vec2f B ) { x += B.x; y += B.y; }
	void operator-=( Vec2f B ) { x -= B.x; y -= B.y; }
	void operator*=( float s ) { x *= s; y *= s; }
	void operator/=( float s ) { x /= s; y /= s; }
	bool operator==( Vec2f B ) { return x == B.x && y == B.y; }
	bool operator!=( Vec2f B ) { return x != B.x || y != B.y; }

	float Length() { return sqrtf( x*x + y*y ); }
	float LengthSq() { return x*x + y*y; }

	void Normalise() {
		float Len = 1.0/sqrtf( x*x + y*y );

		x *= Len;
		y *= Len;
	}
};

#endif // VEC2F_H

//
//#include <math.h>
//#include <ostream>
//using std::ostream;
//
//class Vec2f
//{
//public:
//	// Constructors
//	//Vec2f(void);
//	Vec2f(float _x = 0, float _y = 0);
//	//Vec2f(const Vec2f & rhs);
//
//	~Vec2f(void);
//
//	// Operations with other vectors
//	Vec2f & operator+=(const Vec2f & rhs);
//	Vec2f & operator-=(const Vec2f & rhs);
//	Vec2f operator+(const Vec2f & rhs);
//	Vec2f operator-(const Vec2f & rhs);
//
//	// Special arithmetic
//	float Dot(const Vec2f & rhs) const;
//	//Vec2f Cross(const Vec2f & rhs) const; Missing cross product, I'm not sure if an equivalent exists in 2D FIXME
//
//	Vec2f & operator*=(const float s);
//	Vec2f & operator/=(const float s);
//	Vec2f operator*(const float s);
//	Vec2f operator/(const float s);
//
//	bool operator==(const Vec2f & rhs) const;
//	void operator=(const float & rhs);
//	// Miscellaneous
//	float Length() const;
//	float LengthSqr() const;
//	void Normalise();
//	Vec2f getNormalised();
//	void DumpVec2f(char * s = 0);
//	// Member data
//	float x,y;
//};
//inline Vec2f operator + (const Vec2f &v1,
//						   const Vec2f &v2)
//{
//	return Vec2f(v1.x + v2.x, v1.y + v2.y);
//}
//inline ostream& operator << (ostream& stream, Vec2f& rhs)
//{
//    stream << " x: " << rhs.x << " y: " << rhs.y;
//    return stream;
//}
//inline Vec2f operator - (const Vec2f &v1,
//						   const Vec2f &v2)
//{
//	return Vec2f(v1.x - v2.x, v1.y - v2.y);
//}
//
//inline Vec2f operator - (const Vec2f &v1)
//{
//	return Vec2f(-v1.x, -v1.y);
//}
//
//inline Vec2f operator * (const Vec2f &v,
//						   const float &s)
//{
//	return Vec2f(v.x * s, v.y * s);
//}
//
//inline Vec2f operator * (const float & s,
//						   const Vec2f &v)
//{
//	return Vec2f(v.x * s, v.y * s);
//}
//
//inline Vec2f operator / (const Vec2f &v,
//						   const float & s)
//{
//	return Vec2f(v.x / s, v.y / s);
//}
//
//
//inline float DotProduct(const Vec2f &v1,
//						 const Vec2f &v2)
//{
//	return (v1.x * v2.x + v1.y * v2.y);
//}
//
//inline Vec2f Normalise (const Vec2f &v)
//{
//	return v / v.Length();
//}
//
//

