#include "TileFactory.h"
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Tile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Types/Vec2i.h>

TileFactory::TileFactory(FactoryLoader* loader)
{
    //ctor
    materialName = loader->get<std::string>("materialName","player");
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::StaticGeometryCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::StaticGeometryCategory);

    size = loader->get<Vec2f>("size",Vec2f(1,1));

    //fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
    //fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::CrateCategory);
}

TileFactory::~TileFactory()
{
    //dtor
}

Entity* TileFactory::useFactory(FactoryParameters* parameters)
{
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    Vec2f readDimensions = parameters->get<Vec2f>("size",size);
    if (readDimensions != Vec2f(0,0))
    {
        size = readDimensions;
        shapeDef.SetAsBox(size.x*0.5f,size.y*0.5f);
    }
    Entity* entity = new Tile;

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new StaticSkin(size.x,size.y);
    setMaterial(entity->mSkin,materialName);
    return entity;
}
