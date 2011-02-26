#include "CrateDef.h"
#include <cstring>

CrateDef::CrateDef()
{
    //ctor
    materialName[0] = '\0';
}
CrateDef::CrateDef(float _width, float _height, const char* _materialName)
{
    width = _width;
    height = _height;
    strcpy(materialName,_materialName);
}
