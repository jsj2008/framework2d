#include "StaticSkinFactory.h"
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>

StaticSkinFactory::StaticSkinFactory()
{

}
void StaticSkinFactory::init(FactoryLoader* _loader, AbstractFactories* factories)
{
    //ctor
    materialName = _loader->get<std::string>("materialName","player");
}

StaticSkinFactory::~StaticSkinFactory()
{
    //dtor
}

Skin* StaticSkinFactory::useFactory(FactoryParameters* parameters)
{
    Vec2f dimensions = parameters->get("dimensions", Vec2f(2,2));
    Skin* skin = new StaticSkin(dimensions.x,dimensions.y);
    setMaterial(skin,materialName);
    return skin;
}
