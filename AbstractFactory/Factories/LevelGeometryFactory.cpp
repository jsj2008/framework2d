#include "LevelGeometryFactory.h"
#include <Graphics/GraphicsManager.h>
#include <Entities/StaticGeometry.h>
#include <Graphics/Skins/ConvexPolygonSkin.h>
#include <AI/AIManager.h>
#include <Physics/PhysicsManager.h>
#include <Physics/BodyPart.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/CollisionDatabase.h>

LevelGeometryFactory::LevelGeometryFactory()
{
    //ctor
}

LevelGeometryFactory::~LevelGeometryFactory()
{
    //dtor
}

void LevelGeometryFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin", "ConvexPolygonSkinFactory");
    bodyFactory = loader->getFactory<BodyPart>("body", "SingleFixtureBodyPartFactory");

}

Entity* LevelGeometryFactory::useFactory(FactoryParameters* _parameters)
{
    //g_AIManager.addStaticGeometry(&points[0],points.size());
    StaticGeometry* entity = new StaticGeometry;
    entity->baseInit(skinFactory->use(_parameters, entity));
    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);

    return entity;
}
