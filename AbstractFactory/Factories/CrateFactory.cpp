#include "CrateFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Crate.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>

CrateFactory::CrateFactory(FactoryLoader* loader)
:AbstractFactory()
{
    //ctor
    dimensions = Vec2f(2,2);
    bodyDef.type = b2_dynamicBody;
    fixtureDef.density = loader->get<float>("density",1.0f);
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::CrateCategory);
    shapeDef.SetAsBox(dimensions.x*0.5f,dimensions.y*0.5f);
}

CrateFactory::~CrateFactory()
{
    //dtor
}
Entity* CrateFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    dimensions = parameters->get<Vec2f>("dimensions",dimensions);

    shapeDef.SetAsBox(dimensions.x*0.5f,dimensions.y*0.5f);
    Entity* entity = new Crate;

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = AbstractFactories::useFactory<Skin>("StaticSkinFactory",parameters);
    return entity;
}
