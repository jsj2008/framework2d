#ifndef VEC2F_H
#define VEC2F_H

#include <math.h>
#include <Box2D/Common/b2Settings.h>
bool b2IsValid(float32 x);
#define b2Vec2 Vec2f
struct Vec2f
{
	Vec2f operator*( float s ) { return Vec2f( x*s, y*s ); }
	Vec2f operator/( float s ) { return Vec2f( x/s, y/s ); }
	Vec2f operator+( Vec2f B ) { return Vec2f( x + B.x, y + B.y ); }
	Vec2f operator-( Vec2f B ) { return Vec2f( x - B.x, y - B.y ); }
	Vec2f operator-() { return Vec2f( -x, -y ); }
	float operator*( Vec2f B ) { return x*B.x + y*B.y; }
	void operator/=( float s ) { x /= s; y /= s; }
	bool operator==( Vec2f B ) { return x == B.x && y == B.y; }
	bool operator!=( Vec2f B ) { return x != B.x || y != B.y; }

	Vec2f() {x=y=0;}

	/// Construct using coordinates.
	Vec2f(float32 x, float32 y) : x(x), y(y) {}

	/// Set this vector to all zeros.
	void SetZero() { x = 0.0f; y = 0.0f; }

	/// Set this vector to some specified coordinates.
	void Set(float32 x_, float32 y_) { x = x_; y = y_; }

	/// Negate this vector.
	Vec2f operator -() const { Vec2f v; v.Set(-x, -y); return v; }

	/// Read from and indexed element.
	float32 operator () (int32 i) const
	{
		return (&x)[i];
	}

	/// Write to an indexed element.
	float32& operator () (int32 i)
	{
		return (&x)[i];
	}

	/// Add a vector to this vector.
	void operator += (const Vec2f& v)
	{
		x += v.x; y += v.y;
	}

	/// Subtract a vector from this vector.
	void operator -= (const Vec2f& v)
	{
		x -= v.x; y -= v.y;
	}

	/// Multiply this vector by a scalar.
	void operator *= (float32 a)
	{
		x *= a; y *= a;
	}

	/// Get the length of this vector (the norm).
	float32 Length() const
	{
		return b2Sqrt(x * x + y * y);
	}

	/// Get the length squared. For performance, use this instead of
	/// Vec2f::Length (if possible).
	float32 LengthSquared() const
	{
		return x * x + y * y;
	}

	/// Convert this vector into a unit vector. Returns the length.
	float32 Normalize()
	{
		float32 length = Length();
		if (length < b2_epsilon)
		{
			return 0.0f;
		}
		float32 invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return length;
	}

	/// Does this vector contain finite coordinates?
	bool IsValid() const
	{
		return b2IsValid(x) && b2IsValid(y);
	}

	float32 x, y;
};
/*
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
	Vec2f operator -() const { Vec2f v; v.Set(-x, -y); return v; }
	float32 operator () (int32 i) const
	{
		return (&x)[i];
	}
	float32& operator () (int32 i)
	{
		return (&x)[i];
	}

	void Set(float32 x_, float32 y_) { x = x_; y = y_; }
	void SetZero() { x = 0.0f; y = 0.0f; }
	float Length() { return sqrtf( x*x + y*y ); }
	float LengthSquared() { return x*x + y*y; }
	bool IsValid() const
	{
		return b2IsValid(x) && b2IsValid(y);
	}
	float32 Normalize()
	{
		float32 length = Length();
		if (length < b2_epsilon)
		{
			return 0.0f;
		}
		float32 invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return length;
	}

	void Normalise() {
		float Len = 1.0/sqrtf( x*x + y*y );

		x *= Len;
		y *= Len;
	}
};
*/
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

