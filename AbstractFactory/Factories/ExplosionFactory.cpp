#include "ExplosionFactory.h"
#include <Entities/Explosion.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ExplosionFactory::ExplosionFactory()
{
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
    physicsManager = nullptr;
}
void ExplosionFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    damage = loader->get<float>("damage",0.0f);
    force = loader->get<float>("force",2.0f);
    time = loader->get<float>("time",10.0f);
    shapeDef.m_radius = loader->get<float>("radius",2.0f);
    physicsManager = factories->getWorld();

    skinFactory = loader->getFactory<Skin>("skin", "BubbleSkinFactory");
}

ExplosionFactory::~ExplosionFactory()
{
    //dtor
}
Entity* ExplosionFactory::useFactory(FactoryParameters* parameters)
{
    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));
    Skin* skin = skinFactory->use(parameters);
    Entity* entity = new Explosion(shapeDef.m_radius,damage,force,time, skin);
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);
    return entity;
}
