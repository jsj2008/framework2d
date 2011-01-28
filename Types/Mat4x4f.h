#ifndef MAT4X4F_H
#define MAT4X4F_H
////#include "main.h"

#include "Vec3f.h"

class Mat4x4f
{
public:
	//Mat4x4f(void);
	Mat4x4f(const Mat4x4f & rhs = IDENTITY);
	Mat4x4f(float _elem[][4]);
	Mat4x4f(float _11, float _12, float _13, float _14,
				float _21, float _22, float _23, float _24,
				float _31, float _32, float _33, float _34,
				float _41, float _42, float _43, float _44);
    Mat4x4f(float newElem[16]); // OpenGL - glGetMatrix

	~Mat4x4f(void);

	void Translation(float X, float Y, float Z);
	void Scale(float X, float Y, float Z);
	void RotationX(float fAngle);
	void RotationY(float fAngle);
	void RotationZ(float fAngle);

	void DumpMat4x4f(char * s = NULL);

	void LookAt(const Vec3f & vFrom,
				const Vec3f & vTo,
				const Vec3f & vUp);

	inline float &operator()( unsigned int Row, unsigned int Column )
	{ return elem[Row][Column]; }
	inline float const &operator()( unsigned int Row, unsigned int Column ) const
	{ return elem[Row][Column]; }
	float* asSingleArray(); // WARNING! Delete the memory returned from this function!

	float elem[4][4];
	static const Mat4x4f IDENTITY;
	static const Mat4x4f NULLMATRIX;
};

Mat4x4f operator * ( const Mat4x4f & M1,
					   const Mat4x4f & M2 );

Vec3f operator * ( const Mat4x4f & M,
					 const Vec3f & V );

inline Mat4x4f operator - ( const Mat4x4f & M )
{
	return Mat4x4f(-M(0,0),-M(0,1),-M(0,2),-M(0,3),
					 -M(1,0),-M(1,1),-M(1,2),-M(1,3),
					 -M(2,0),-M(2,1),-M(2,2),-M(2,3),
					 -M(3,0),-M(3,1),-M(3,2),-M(3,3));
}

inline Mat4x4f operator - ( const Mat4x4f & M1,
							  const Mat4x4f & M2 )
{
	return Mat4x4f(M1(0,0)-M2(0,0),M1(0,1)-M2(0,1),M1(0,2)-M2(0,2),M1(0,3)-M2(0,3),
					 M1(1,0)-M2(1,0),M1(1,1)-M2(1,1),M1(1,2)-M2(1,2),M1(1,3)-M2(1,3),
					 M1(2,0)-M2(2,0),M1(2,1)-M2(2,1),M1(2,2)-M2(2,2),M1(2,3)-M2(2,3),
					 M1(3,0)-M2(3,0),M1(3,1)-M2(3,1),M1(3,2)-M2(3,2),M1(3,3)-M2(3,3));
}

inline Mat4x4f operator + ( const Mat4x4f & M1,
							  const Mat4x4f & M2 )
{
	return Mat4x4f(M1(0,0)+M2(0,0),M1(0,1)+M2(0,1),M1(0,2)+M2(0,2),M1(0,3)+M2(0,3),
					 M1(1,0)+M2(1,0),M1(1,1)+M2(1,1),M1(1,2)+M2(1,2),M1(1,3)+M2(1,3),
					 M1(2,0)+M2(2,0),M1(2,1)+M2(2,1),M1(2,2)+M2(2,2),M1(2,3)+M2(2,3),
					 M1(3,0)+M2(3,0),M1(3,1)+M2(3,1),M1(3,2)+M2(3,2),M1(3,3)+M2(3,3));
}

inline Mat4x4f operator * ( const Mat4x4f & M,
							  const float & s )
{
	return Mat4x4f(M(0,0) * s,M(0,1) * s,M(0,2) * s,M(0,3) * s,
					 M(1,0) * s,M(1,1) * s,M(1,2) * s,M(1,3) * s,
					 M(2,0) * s,M(2,1) * s,M(2,2) * s,M(2,3) * s,
					 M(3,0) * s,M(3,1) * s,M(3,2) * s,M(3,3) * s);
}

inline Mat4x4f operator * ( const float & s,
							  const Mat4x4f & M )
{
	return Mat4x4f(M(0,0) * s,M(0,1) * s,M(0,2) * s,M(0,3) * s,
					 M(1,0) * s,M(1,1) * s,M(1,2) * s,M(1,3) * s,
					 M(2,0) * s,M(2,1) * s,M(2,2) * s,M(2,3) * s,
					 M(3,0) * s,M(3,1) * s,M(3,2) * s,M(3,3) * s);
}

inline Mat4x4f Transpose( Mat4x4f const & M )
{
	Mat4x4f ret;

	for(int j = 0; j < 4; j++)
	{
		for(int i = 0; i < 4; i++)
		{
			ret(i,j) = M(j,i);
		}
	}

	return ret;
}

#endif // MAT4X4F_H
