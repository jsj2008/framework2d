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
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::StaticGeometryCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::StaticGeometryCategory);
}
void LevelGeometryFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
}

LevelGeometryFactory::~LevelGeometryFactory()
{
    //dtor
}

Entity* LevelGeometryFactory::useFactory(FactoryParameters* parameters)
{
    std::vector<Vec2f> points = parameters->get<std::vector<Vec2f>>("points",{});

    //g_AIManager.addStaticGeometry(&points[0],points.size());
    StaticGeometry* entity = new StaticGeometry;

    assert(points.size() <= b2_maxPolygonVertices);

    shapeDef.Set(&points[0],points.size());

    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new ConvexPolygonSkin(&points[0],points.size());
    setMaterial(entity->mSkin,parameters->get<std::string>("materialName","").c_str());

    return entity;
}
