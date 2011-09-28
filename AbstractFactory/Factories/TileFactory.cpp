#include "TileFactory.h"
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Tile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Types/Vec2i.h>

TileFactory::TileFactory()
{
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::StaticGeometryCategory;
    physicsManager = nullptr;
}
void TileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    skinFactory = loader->getFactory<Skin>("skin", "StaticSkinFactory");
    physicsManager = factories->getWorld();
    fixtureDef.filter.maskBits = physicsManager->getCollisionMask(PhysicsManager::StaticGeometryCategory);
}

TileFactory::~TileFactory()
{
    //dtor
}

Entity* TileFactory::useFactory(FactoryParameters* parameters)
{
    Skin* skin = skinFactory->use(parameters);
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    Vec2f readDimensions = parameters->get<Vec2f>("size",Vec2f(1,1));
    shapeDef.SetAsBox(readDimensions.x*0.5f,readDimensions.y*0.5f);

    Entity* entity = new Tile(skin);

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);

    return entity;
}

