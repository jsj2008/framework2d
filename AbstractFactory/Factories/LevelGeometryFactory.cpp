#include "LevelGeometryFactory.h"
#include <Graphics/GraphicsManager.h>
#include <Entities/StaticGeometry.h>
#include <Graphics/Skins/ConvexPolygonSkin.h>
#include <AI/AIManager.h>
#include <Physics/PhysicsManager.h>
#include <Physics/Body.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/CollisionResponse.h>

LevelGeometryFactory::LevelGeometryFactory()
{
    //ctor
    physicsManager = nullptr;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::StaticGeometryCategory;
}

LevelGeometryFactory::~LevelGeometryFactory()
{
    //dtor
}

void LevelGeometryFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin", "ConvexPolygonSkinFactory");

    physicsManager = factories->getWorld();
    fixtureDef.filter.maskBits = physicsManager->getCollisionMask(PhysicsManager::StaticGeometryCategory);
    //collisionResponse = factories->getFactory<CollisionResponse>(loader->get<std::string>("collisionResponse", "CollisionResponseFactory"));
    collisionResponse = loader->getFactory<CollisionResponse>("collisionResponse", "CollisionResponseFactory");
}

Entity* LevelGeometryFactory::useFactory(FactoryParameters* parameters)
{
    std::vector<Vec2f> points = parameters->getArray<Vec2f>("points",{{0,0},{1,1},{-2,1}});

    //g_AIManager.addStaticGeometry(&points[0],points.size());
    Skin* skin = skinFactory->use(parameters);

    StaticGeometry* entity = new StaticGeometry(skin);

    assert(points.size() <= b2_maxPolygonVertices);

    shapeDef.Set(&points[0],points.size());

    bodyDef.userData = (void*)entity;
    Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    fixtureDef.userData = collisionResponse->use(parameters);
    assert(fixtureDef.userData);
    body->createFixture(&fixtureDef);

    return entity;
}
