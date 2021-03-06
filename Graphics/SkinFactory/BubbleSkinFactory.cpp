#include "BubbleSkinFactory.h"
#include <Graphics/GraphicsManager.h> /// FIXME
#include <Graphics/Skins/BubbleSkin.h>

BubbleSkinFactory::BubbleSkinFactory()
{
    //ctor
}

BubbleSkinFactory::~BubbleSkinFactory()
{
    //dtor
}

void BubbleSkinFactory::init(FactoryLoader* _loader, AbstractFactories* factories)
{
    //ctor
    materialName = _loader->get<std::string>("materialName","player");
    radius = _loader->get<float>("radius",2.0f);
}

Skin* BubbleSkinFactory::useFactory(FactoryParameters* _parameters)
{
    Skin* skin = new BubbleSkin(radius);
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
    return skin;
}
