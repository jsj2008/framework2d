#include "AIEntityDef.h"
#include <cstring>

AIEntityDef::AIEntityDef(const char* _materialName, float _width, float _height, BrainType _aiType, const char* _weapon)
{
    setMaterial(_materialName);
    width = _width;
    height = _height;
    aiType = _aiType;
    strcpy(weapon,"pistol");
}
