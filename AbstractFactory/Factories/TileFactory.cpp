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
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::StaticGeometryCategory);
}
void TileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    materialName = loader->get<std::string>("materialName","player");
    size = loader->get<Vec2f>("size",Vec2f(1,1));
}

TileFactory::~TileFactory()
{
    //dtor
}

Entity* TileFactory::useFactory(FactoryParameters* parameters)
{
    Skin* skin = new StaticSkin(size.x,size.y);
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    Vec2f readDimensions = parameters->get<Vec2f>("size",size);
    if (readDimensions != Vec2f(0,0))
    {
        size = readDimensions;
        shapeDef.SetAsBox(size.x*0.5f,size.y*0.5f);
    }
    Entity* entity = new Tile(skin);

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    b2Body* body = g_PhysicsManager.createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);

    setMaterial(skin,materialName);
    return entity;
}

