#include "StaticSkinFactory.h"
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Graphics/GraphicsManager.h> /// FIXME
#include <AbstractFactory/FactoryParameters.h>

StaticSkinFactory::StaticSkinFactory()
{

}
StaticSkinFactory::~StaticSkinFactory()
{
    //dtor
}

void StaticSkinFactory::init(FactoryLoader* _loader, AbstractFactories* factories)
{
    //ctor
    materialName = _loader->get<std::string>("materialName","player");
}

Skin* StaticSkinFactory::useFactory(FactoryParameters* parameters)
{
    Vec2f dimensions = parameters->get("dimensions", Vec2f(2,2));
    Skin* skin = new StaticSkin(dimensions.x,dimensions.y);
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
    return skin;
}
