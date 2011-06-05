#include "ExplosionFactory.h"
#include <Entities/Explosion.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ExplosionFactory::ExplosionFactory(FactoryLoader* loader)
{
    //ctor
    material = loader->getString("material","defaultBubble");
    damage = loader->getFloat("damage",0.0f);
    force = loader->getFloat("force",2.0f);
    time = loader->getFloat("time",10.0f);
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
    shapeDef.m_radius = loader->getFloat("radius",2.0f);
}

ExplosionFactory::~ExplosionFactory()
{
    //dtor
}
Entity* ExplosionFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    bodyDef.position = parameters->getVec2f("");//params->position;
    Entity* entity = new Explosion(shapeDef.m_radius,damage,force,time, new BubbleSkin(shapeDef.m_radius));
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);
    setMaterial(entity->mSkin,material);
    return entity;
}
