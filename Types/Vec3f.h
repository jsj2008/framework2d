#ifndef VEC3F_H
#define VEC3F_H

#include <math.h>
#include <ostream>
using std::ostream;

class Vec3f
{
public:
	// Constructors
	//Vec3f(void);
	Vec3f(float _x = 0, float _y = 0, float _z = 0);
	//Vec3f(const Vec3f & rhs);

	~Vec3f(void);

	// Operations with other vectors
	Vec3f & operator+=(const Vec3f & rhs);
	Vec3f & operator-=(const Vec3f & rhs);

	// Special arithmetic
	float Dot3(const Vec3f & rhs) const;
	Vec3f Cross(const Vec3f & rhs) const;

	Vec3f & operator*=(const float s);
	Vec3f & operator/=(const float s);

	bool operator==(const Vec3f & rhs) const;
	void operator=(const float & rhs);
	// Miscellaneous
	float Length() const;
	float LengthSqr() const;
	Vec3f Normalise();
	void NormaliseSelf();
	void DumpVec3f(char * s = 0);
	// Member data
	float x,y,z;
};
inline Vec3f operator + (const Vec3f &v1,
						   const Vec3f &v2)
{
	return Vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline ostream& operator << (ostream& stream, Vec3f& rhs)
{
    stream << " x: " << rhs.x << " y: " << rhs.y << " z: " << rhs.z;
    return stream;
}
inline Vec3f operator - (const Vec3f &v1,
						   const Vec3f &v2)
{
	return Vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3f operator - (const Vec3f &v1)
{
	return Vec3f(-v1.x, -v1.y, -v1.z);
}

inline Vec3f operator * (const Vec3f &v,
						   const float &s)
{
	return Vec3f(v.x * s, v.y * s, v.z * s);
}

inline Vec3f operator * (const float & s,
						   const Vec3f &v)
{
	return Vec3f(v.x * s, v.y * s, v.z * s);
}

inline Vec3f operator / (const Vec3f &v,
						   const float & s)
{
	return Vec3f(v.x / s, v.y / s, v.z / s);
}

inline Vec3f CrossProduct (const Vec3f &v1,
							 const Vec3f &v2)
{
	return Vec3f(v1.y * v2.z - v1.z * v2.y,
				   v1.z * v2.x - v1.x * v2.z,
				   v1.x * v2.y - v1.y * v2.x);
}


inline float DotProduct3(const Vec3f &v1,
						 const Vec3f &v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline Vec3f Normalise (const Vec3f &v)
{
	return v / v.Length();
}

#endif // VEC3F_H
