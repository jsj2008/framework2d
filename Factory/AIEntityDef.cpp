#include "AIEntityDef.h"

void AIEntityDef::set(const char* _materialName, float _width, float _height, BrainType _aiType)
{
    setMaterial(_materialName);
    width = _width;
    height = _height;
    aiType = _aiType;
}
