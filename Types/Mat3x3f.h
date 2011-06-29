#ifndef MAT3X3F_H
#define MAT3X3F_H
////#include "main.h"

#include "Vec2f.h"

class Mat3x3f
{
public:
	//Mat3x3f(void);
	Mat3x3f(const Mat3x3f & rhs = IDENTITY);
	Mat3x3f(float _elem[][3]);
	Mat3x3f(float _11, float _12, float _13,
				float _21, float _22, float _23,
				float _31, float _32, float _33);
    Mat3x3f(float newElem[9]);

	~Mat3x3f(void);

	void Translation(float X, float Y);
	void Rotation(float fAngle);// anticlockwise

	void DumpMat3x3f(char * s = nullptr);

	inline float &operator()( unsigned int Row, unsigned int Column )
	{ return elem[Row][Column]; }
	inline float const &operator()( unsigned int Row, unsigned int Column ) const
	{ return elem[Row][Column]; }
	float* asSingleArray(); // WARNING! Delete the memory returned from this function!

	float elem[3][3];
	static const Mat3x3f IDENTITY;
	static const Mat3x3f nullptrMATRIX;
};

Mat3x3f operator * ( const Mat3x3f & M1,
					   const Mat3x3f & M2 );

Vec2f operator * ( const Mat3x3f & M,
					 const Vec2f & V );

inline Mat3x3f operator - ( const Mat3x3f & M )
{
	return Mat3x3f(-M(0,0),-M(0,1),-M(0,2),
					 -M(1,0),-M(1,1),-M(1,2),
					 -M(2,0),-M(2,1),-M(2,2));
}

inline Mat3x3f operator - ( const Mat3x3f & M1,
							  const Mat3x3f & M2 )
{
	return Mat3x3f(M1(0,0)-M2(0,0),M1(0,1)-M2(0,1),M1(0,2)-M2(0,2),
					 M1(1,0)-M2(1,0),M1(1,1)-M2(1,1),M1(1,2)-M2(1,2),
					 M1(2,0)-M2(2,0),M1(2,1)-M2(2,1),M1(2,2)-M2(2,2));
}

inline Mat3x3f operator + ( const Mat3x3f & M1,
							  const Mat3x3f & M2 )
{
	return Mat3x3f(M1(0,0)+M2(0,0),M1(0,1)+M2(0,1),M1(0,2)+M2(0,2),
					 M1(1,0)+M2(1,0),M1(1,1)+M2(1,1),M1(1,2)+M2(1,2),
					 M1(2,0)+M2(2,0),M1(2,1)+M2(2,1),M1(2,2)+M2(2,2));
}

inline Mat3x3f operator * ( const Mat3x3f & M,
							  const float & s )
{
	return Mat3x3f(M(0,0) * s,M(0,1) * s,M(0,2) * s,
					 M(1,0) * s,M(1,1) * s,M(1,2) * s,
					 M(2,0) * s,M(2,1) * s,M(2,2) * s);
}

inline Mat3x3f operator * ( const float & s,
							  const Mat3x3f & M )
{
	return Mat3x3f(M(0,0) * s,M(0,1) * s,M(0,2) * s,
					 M(1,0) * s,M(1,1) * s,M(1,2) * s,
					 M(2,0) * s,M(2,1) * s,M(2,2) * s);
}

inline Mat3x3f Transpose( Mat3x3f const & M )
{
	Mat3x3f ret;

	for(int j = 0; j < 3; j++)
	{
		for(int i = 0; i < 3; i++)
		{
			ret(i,j) = M(j,i);
		}
	}

	return ret;
}

#endif // MAT3X3F_H
