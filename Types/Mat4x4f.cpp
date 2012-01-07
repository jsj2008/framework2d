#include <memory.h>
#include <stdio.h>
//#include "maths.h"
#include "Mat4x4f.h"

const Mat4x4f Mat4x4f::IDENTITY(1.0f,0.0f,0.0f,0.0f,
									0.0f,1.0f,0.0f,0.0f,
									0.0f,0.0f,1.0f,0.0f,
									0.0f,0.0f,0.0f,1.0f);

const Mat4x4f Mat4x4f::nullptrMATRIX(0.0f,0.0f,0.0f,0.0f,
									  0.0f,0.0f,0.0f,0.0f,
									  0.0f,0.0f,0.0f,0.0f,
									  0.0f,0.0f,0.0f,0.0f);

/*Mat4x4f::Mat4x4f(void)
{
}*/

Mat4x4f::~Mat4x4f(void)
{
}

Mat4x4f::Mat4x4f(const Mat4x4f & rhs)
{
	memcpy(elem, rhs.elem, sizeof(float) * 16);
}

Mat4x4f::Mat4x4f(float _11, float _12, float _13, float _14,
					 float _21, float _22, float _23, float _24,
					 float _31, float _32, float _33, float _34,
					 float _41, float _42, float _43, float _44)
{
	elem[0][0] = _11;	elem[0][1] = _12;	elem[0][2] = _13;	elem[0][3] = _14;
	elem[1][0] = _21;	elem[1][1] = _22;	elem[1][2] = _23;	elem[1][3] = _24;
	elem[2][0] = _31;	elem[2][1] = _32;	elem[2][2] = _33;	elem[2][3] = _34;
	elem[3][0] = _41;	elem[3][1] = _42;	elem[3][2] = _43;	elem[3][3] = _44;
}

Mat4x4f::Mat4x4f(float _elem[][4])
{
	memcpy(elem, _elem, sizeof(float) * 16);
}
Mat4x4f::Mat4x4f(float newElem[16])
{
    memcpy(elem,newElem,sizeof(float) * 16);
}
Mat4x4f operator*( const Mat4x4f &M1,
                     const Mat4x4f &M2)
{
    Mat4x4f ret;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            float Value = 0;

            for(int k = 0; k < 4; k++)
            {
                Value += M1(i,k) * M2(k,j);
            }

            ret(i,j) = Value;
        }
    }

    return ret;
}

Vec3f operator * ( const Mat4x4f &M,
					 const Vec3f &V )
{
    Vec3f ret;

	ret.x = M(0,0) * V.x + M(1,0) * V.y + M(2,0) * V.z + M(3,0);
	ret.y = M(0,1) * V.x + M(1,1) * V.y + M(2,1) * V.z + M(3,1);
	ret.z = M(0,2) * V.x + M(1,2) * V.y + M(2,2) * V.z + M(3,2);
	float w = M(0,3) * V.x + M(1,3) * V.y + M(2,3) * V.z + M(3,3);
	ret /= w;
    return ret;
}

void Mat4x4f::Translation(float X, float Y, float Z)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 16);

	elem[3][0] = X;
	elem[3][1] = Y;
	elem[3][2] = Z;
}

void Mat4x4f::Scale(float X, float Y, float Z)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 16);

	elem[0][0] = X;
	elem[1][1] = Y;
	elem[2][2] = Z;
}

void Mat4x4f::RotationX(float fAngle)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 16);
	float c = cos(fAngle);
	float s = sin(fAngle);
	elem[1][1] = c;
	elem[1][2] = s;
	elem[2][1] = -s;
	elem[2][2] = c;
}

void Mat4x4f::RotationY(float fAngle)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 16);
	float c = cos(fAngle);
	float s = sin(fAngle);
	elem[0][0] = c;
	elem[2][0] = s;
	elem[0][2] = -s;
	elem[2][2] = c;
}

void Mat4x4f::RotationZ(float fAngle)
{
	memcpy(elem, IDENTITY.elem, sizeof(float) * 16);
	float c = cos(fAngle);
	float s = sin(fAngle);
	elem[0][0] = c;
	elem[0][1] = s;
	elem[1][0] = -s;
	elem[1][1] = c;
}

void Mat4x4f::LookAt(const Vec3f & vFrom, const Vec3f & vTo, const Vec3f & vUp)
{
	Vec3f vZ = Normalise(vFrom - vTo);
	//vZ.DumpVec3f("vZ");
	Vec3f vX = Normalise(vUp.Cross(vZ));
	//vX.DumpVec3f("vX");
	Vec3f vY = vZ.Cross(vX);
	//vY.DumpVec3f("vY");

    elem[0][0] = vX.x;	elem[0][1] = vY.x;	elem[0][2] = vZ.x;	elem[0][3] = 0;
	elem[1][0] = vX.y;	elem[1][1] = vY.y;	elem[1][2] = vZ.y;	elem[1][3] = 0;
	elem[2][0] = vX.z;	elem[2][1] = vY.z;	elem[2][2] = vZ.z;	elem[2][3] = 0;

	elem[3][0] = -vX.Dot3(vFrom);
	elem[3][1] = -vY.Dot3(vFrom);
	elem[3][2] = -vZ.Dot3(vFrom);
	elem[3][3] = 1;
}
float* Mat4x4f::asSingleArray()
{
    float* a;
    a = new float[16];
    memcpy(a,elem[0],sizeof(float) * 4);
    memcpy(a+4,elem[1],sizeof(float) * 4);
    memcpy(a+8,elem[2],sizeof(float) * 4);
    memcpy(a+12,elem[3],sizeof(float) * 4);
    return a;
}
void Mat4x4f::DumpMat4x4f(char * s)
{
	if(s != nullptr)printf("\n%s\n",s);
	else printf("\n");
	printf("%f %f %f %f\n",   elem[0][0], elem[0][1], elem[0][2], elem[0][3]);
	printf("%f %f %f %f\n",   elem[1][0], elem[1][1], elem[1][2], elem[1][3]);
	printf("%f %f %f %f\n",   elem[2][0], elem[2][1], elem[2][2], elem[2][3]);
	printf("%f %f %f %f\n\n", elem[3][0], elem[3][1], elem[3][2], elem[3][3]);
}
