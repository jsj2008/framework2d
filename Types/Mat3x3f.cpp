#include <memory.h>
#include <stdio.h>
//#include "maths.h"
#include "Mat3x3f.h"

const Mat3x3f Mat3x3f::IDENTITY(1.0f,0.0f,0.0f,
									0.0f,1.0f,0.0f,
									0.0f,0.0f,1.0f);

const Mat3x3f Mat3x3f::nullptrMATRIX(0.0f,0.0f,0.0f,
									  0.0f,0.0f,0.0f,
									  0.0f,0.0f,0.0f);

/*Mat3x3f::Mat3x3f(void)
{
}*/

Mat3x3f::~Mat3x3f(void)
{
}

Mat3x3f::Mat3x3f(const Mat3x3f & rhs)
{
	memcpy(elem, rhs.elem, sizeof(float) * 9);
}

Mat3x3f::Mat3x3f(float _11, float _12, float _13,
					 float _21, float _22, float _23,
					 float _31, float _32, float _33)
{
	elem[0][0] = _11;	elem[0][1] = _12;	elem[0][2] = _13;
	elem[1][0] = _21;	elem[1][1] = _22;	elem[1][2] = _23;
	elem[2][0] = _31;	elem[2][1] = _32;	elem[2][2] = _33;
}

Mat3x3f::Mat3x3f(float _elem[][3])
{
	memcpy(elem, _elem, sizeof(float) * 9);
}
Mat3x3f::Mat3x3f(float newElem[9])
{
    memcpy(elem,newElem,sizeof(float) * 9);
}
Mat3x3f operator*( const Mat3x3f &M1,
                     const Mat3x3f &M2)
{
    Mat3x3f ret;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            float Value = 0;

            for(int k = 0; k < 3; k++)
            {
                Value += M1(i,k) * M2(k,j);
            }

            ret(i,j) = Value;
        }
    }

    return ret;
}
Vec2f operator * ( const Mat3x3f &M,
					 const Vec2f &V )
{
    Vec2f ret;
	ret.x = M(0,0) * V.x + M(1,0) * V.y + M(2,0);
	ret.y = M(0,1) * V.x + M(1,1) * V.y + M(2,1);
	float z = M(0,2) * V.x + M(1,2) * V.y + M(2,2);
	ret /= z;
    return ret;
}

void Mat3x3f::Translation(float X, float Y)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 9);

	elem[2][0] = X;
	elem[2][1] = Y;
}

void Mat3x3f::Rotation(float fAngle)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 9);
	float c = cos(fAngle);
	float s = sin(fAngle);
	elem[0][0] = c;
	elem[0][1] = s;
	elem[1][0] = -s;
	elem[1][1] = c;
}

float* Mat3x3f::asSingleArray()
{
    float* a;
    a = new float[9];
    memcpy(a,elem[0],sizeof(float) * 3);
    memcpy(a+3,elem[1],sizeof(float) * 3);
    memcpy(a+6,elem[2],sizeof(float) * 3);
    return a;
}
void Mat3x3f::DumpMat3x3f(char * s)
{
	if(s != nullptr)printf("\n%s\n",s);
	else printf("\n");
	printf("%f %f %f\n",   elem[0][0], elem[0][1], elem[0][2]);
	printf("%f %f %f\n",   elem[1][0], elem[1][1], elem[1][2]);
	printf("%f %f %f\n",   elem[2][0], elem[2][1], elem[2][2]);
}
