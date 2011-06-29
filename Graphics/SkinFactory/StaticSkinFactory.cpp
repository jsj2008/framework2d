#include "StaticSkinFactory.h"
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>

StaticSkinFactory::StaticSkinFactory(FactoryLoader* _loader)
{
    //ctor
    materialName = _loader->get<std::string>("materialName","player");
    dimensions = _loader->get<Vec2f>("dimensions",Vec2f(2,2));
}

StaticSkinFactory::~StaticSkinFactory()
{
    //dtor
}

Skin* StaticSkinFactory::useFactory(FactoryParameters* parameters)
{
    dimensions = parameters->get("dimensions", dimensions);
    Skin* skin = new StaticSkin(dimensions.x,dimensions.y);
    setMaterial(skin,materialName);
    return skin;
}
