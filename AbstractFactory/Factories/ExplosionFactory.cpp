#include "ExplosionFactory.h"
#include <Entities/Explosion.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ExplosionFactory::ExplosionFactory(FactoryLoader* loader)
{
    //ctor
    material = loader->get<std::string>("material","defaultBubble");
    damage = loader->get<float>("damage",0.0f);
    force = loader->get<float>("force",2.0f);
    time = loader->get<float>("time",10.0f);
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
    shapeDef.m_radius = loader->get<float>("radius",2.0f);
}

ExplosionFactory::~ExplosionFactory()
{
    //dtor
}
Entity* ExplosionFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));//params->position;
    Entity* entity = new Explosion(shapeDef.m_radius,damage,force,time, new BubbleSkin(shapeDef.m_radius));
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);
    setMaterial(entity->mSkin,material);
    return entity;
}