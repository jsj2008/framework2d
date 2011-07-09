#include "ProjectileFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Projectile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ProjectileFactory::ProjectileFactory()
{
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
}
void ProjectileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    expiryTime = loader->get<float>("expiryTime",10.0f);
    radius = loader->get<float>("radius",1.0f);
    shapeDef.m_radius = radius; /// FIXME just spotted this
    explosion = loader->get<std::string>("explosion","explosion");
    material = loader->get<std::string>("material","Bullet");
}

ProjectileFactory::~ProjectileFactory()
{
    //dtor
}

Entity* ProjectileFactory::useFactory(FactoryParameters* parameters)
{
    //PositionVelocityParameters* params = (PositionVelocityParameters*)parameters;
    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));// params->position;
    bodyDef.linearVelocity = parameters->get<Vec2f>("v",Vec2f(1,0));//params->velocity;
    Entity* entity = new Projectile(explosion, new StaticSkin(radius,radius));
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);
    setMaterial(entity->mSkin,material);
    return entity;
}
