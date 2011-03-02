#include "CrateDef.h"
#include <cstring>

void CrateDef::set(float _width, float _height, const char* _materialName)
{
    width = _width;
    height = _height;
    strcpy(materialName,_materialName);
}

void PlayerDef::set(float _width, float _height, const char* _materialName)
{
    width = _width;
    height = _height;
    strcpy(materialName,_materialName);
}
