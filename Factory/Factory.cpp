#include "Factory.h"
#include <Graphics/Skins/Skin.h>

Factory::Factory()
{
    //ctor
}

Factory::~Factory()
{
    //dtor
}

void Factory::setMaterial(Skin* skin, MaterialContext* material)
{
    skin->material = material;
}
