#include "CrateFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Entities/Crate.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>

CrateFactory::CrateFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::CrateCategory);
}

CrateFactory::~CrateFactory()
{
    //dtor
}

void CrateFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    fixtureDef.density = loader->get<float>("density",1.0f);
    skinFactory = factories->getFactory<Skin>("StaticSkinFactory");
}
Entity* CrateFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Vec2f position(parameters->get<Vec2f>("position", Vec2f(0,0)));
    Vec2f dimensions = parameters->get<Vec2f>("dimensions",Vec2f(2,2));

    shapeDef.SetAsBox(dimensions.x*0.5f,dimensions.y*0.5f);
    Entity* entity = new Crate;

    bodyDef.position = position;
    //bodyDef.angle = params->rotation;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = skinFactory->use(parameters);
    return entity;
}
