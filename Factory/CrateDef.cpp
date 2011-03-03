#include "CrateDef.h"
#include <cstring>

void CrateDef::set(const Vec2f dimensions, float _density, const char* _materialName)
{
    width = dimensions.x;
    height = dimensions.y;
    density = _density;
    strcpy(materialName,_materialName);
}

void PlayerDef::set(float _width, float _height, const char* _materialName)
{
    width = _width;
    height = _height;
    strcpy(materialName,_materialName);
}
