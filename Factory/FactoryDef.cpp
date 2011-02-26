#include "FactoryDef.h"
#include <cstring>

FactoryDef::FactoryDef()
{
    //ctor
}

void FactoryDef::setMaterial(const char* _materialName)
{
    strcpy(materialName,_materialName);
}
