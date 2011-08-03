#include "LevelGeometryFactory.h"
#include <Graphics/GraphicsManager.h>
#include <Entities/StaticGeometry.h>
#include <Graphics/Skins/ConvexPolygonSkin.h>
#include <AI/AIManager.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryParameters.h>

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
    physicsManager = factories->getWorld();
    fixtureDef.filter.maskBits = physicsManager->getCollisionMask(PhysicsManager::StaticGeometryCategory);
}

Entity* LevelGeometryFactory::useFactory(FactoryParameters* parameters)
{
    std::vector<Vec2f> points = parameters->get<std::vector<Vec2f>>("points",{{0,0},{1,1},{-2,1}});

    //g_AIManager.addStaticGeometry(&points[0],points.size());
    Skin* skin = new ConvexPolygonSkin(&points[0],points.size());
    StaticGeometry* entity = new StaticGeometry(skin);

    assert(points.size() <= b2_maxPolygonVertices);

    shapeDef.Set(&points[0],points.size());

    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);

    setMaterial(skin, parameters->get<std::string>("materialName","").c_str());

    return entity;
}
