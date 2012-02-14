#ifndef VEC2F_H
#define VEC2F_H

#include <math.h>
#include <Box2D/Common/b2Math.h>
#include <istream>
#include <ostream>
bool b2IsValid(float32 x);
/*struct Vec2f
{
	Vec2f operator*( float s ) const{ return Vec2f( x*s, y*s ); }
	Vec2f operator/( float s ) const{ return Vec2f( x/s, y/s ); }
	Vec2f operator+(const Vec2f B ) const{ return Vec2f( x + B.x, y + B.y ); }
	Vec2f operator-(const Vec2f B ) const{ return Vec2f( x - B.x, y - B.y ); }
	Vec2f operator-() { return Vec2f( -x, -y ); }
	float operator*( Vec2f B ) const{ return x*B.x + y*B.y; }
	void operator/=( float s ) { x /= s; y /= s; }
	void operator/=( Vec2f B ) { x /= B.x; y /= B.y; }
	bool operator==( Vec2f B ) { return x == B.x && y == B.y; }
	bool operator!=( Vec2f B ) { return x != B.x || y != B.y; }

	Vec2f() {x=y=0.0f;}

	/// Construct using coordinates.
	Vec2f(float32 _x, float32 _y) : x(_x), y(_y) {}

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
    friend std::ostream& operator<< (std::ostream &out, Vec2f &vec);
    friend std::istream& operator>> (std::istream &in, Vec2f &vec);

	float32 x, y;
};*/

//float operator*(Vec2f A, Vec2f B ){ return A.x*B.x + A.y*B.y; }

float intersectionValue(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd); /// Returns the intersection point on _a
Vec2f intersectionPosition(Vec2f _aStart, Vec2f _aEnd, Vec2f _bStart, Vec2f _bEnd);
Vec2f positionFromScalarValue(Vec2f _start, Vec2f _end, float _scalar);
inline Vec2f operator*(Vec2f a, float s ){ return Vec2f( a.x*s, a.y*s ); }

std::ostream& operator<< (std::ostream &out, Vec2f &vec);
std::istream& operator>> (std::istream &in, Vec2f &vec);

inline void operator/=(Vec2f& a, float s ) { a.x /= s; a.y /= s; }
inline void operator/=(Vec2f& a,  Vec2f B ) { a.x /= B.x; a.y /= B.y; }

#endif // VEC2F_H


