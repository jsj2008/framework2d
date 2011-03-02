#include "FactoryDef.h"
#include <cstring>

/*FactoryDef::FactoryDef()
{
    //ctor
    materialName[0] = '\0';
    position = Vec2f(0,0);
}*/

void FactoryDef::setMaterial(const char* _materialName)
{
    strcpy(materialName,_materialName);
}

void FactoryDef::setPosition(const Vec2f position)
{
    xPosition = position.x;
    yPosition = position.y;
}

const Vec2f FactoryDef::getPosition()
{
    return Vec2f(xPosition,yPosition);
}
