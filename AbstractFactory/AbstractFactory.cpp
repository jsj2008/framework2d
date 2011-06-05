#include "AbstractFactory.h"
#include <Graphics/GraphicsManager.h>

AbstractFactory::AbstractFactory()
{
    //ctor
}

AbstractFactory::~AbstractFactory()
{
    //dtor
}
void AbstractFactory::setMaterial(class Skin* skin,const std::string& materialName)
{
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
}
