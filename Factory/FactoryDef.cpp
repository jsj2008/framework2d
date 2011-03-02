#include "FactoryDef.h"
#include <cstring>

FactoryDef::FactoryDef()
{
    //ctor
    materialName[0] = '\0';
}

void FactoryDef::setMaterial(const char* _materialName)
{
    strcpy(materialName,_materialName);
}
