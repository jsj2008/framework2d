#include "ConvexPolygonSkinFactory.h"
#include <Graphics/Skins/ConvexPolygonSkin.h>
#include <Graphics/GraphicsManager.h> /// FIXME

ConvexPolygonSkinFactory::ConvexPolygonSkinFactory()
{
    //ctor
}

ConvexPolygonSkinFactory::~ConvexPolygonSkinFactory()
{
    //dtor
}

void ConvexPolygonSkinFactory::init(FactoryLoader* _loader, AbstractFactories* factories)
{
    //ctor
    materialName = _loader->get<std::string>("materialName","player");
}

Skin* ConvexPolygonSkinFactory::useFactory(FactoryParameters* parameters)
{
    std::vector<Vec2f> points = parameters->getArray<Vec2f>("points",{{0,0},{1,1},{-2,1}});
    Skin* skin = new ConvexPolygonSkin(&points[0],points.size());
    skin->material = g_GraphicsManager.getMaterial(materialName.c_str());
    return skin;
}
