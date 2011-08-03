#include "CrateFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Crate.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>

CrateFactory::CrateFactory()
{
    //ctor
    physicsManager = nullptr;
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
}

CrateFactory::~CrateFactory()
{
    //dtor
}

void CrateFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    fixtureDef.density = loader->get<float>("density",1.0f);
    std::string skinFactoryName = loader->get<std::string>("material","StaticSkinFactory");
    skinFactory = factories->getFactory<Skin>(skinFactoryName);
    physicsManager = factories->getWorld();
    fixtureDef.filter.maskBits = physicsManager->getCollisionMask(PhysicsManager::CrateCategory);
}
Entity* CrateFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    Vec2f dimensions = parameters->get<Vec2f>("dimensions",Vec2f(2,2));

    shapeDef.SetAsBox(dimensions.x*0.5f,dimensions.y*0.5f);
    Entity* entity = new Crate(skinFactory->use(parameters));

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);

    return entity;
}
