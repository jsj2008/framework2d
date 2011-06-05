#include "ProjectileFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Projectile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Physics/PhysicsManager.h>

ProjectileFactory::ProjectileFactory()
{
    //ctor
    velocity = Vec2f(0,5);
    expiryTime = 10.0f;
    radius = 1.0f;
    explosion = "explosion";
    material = "Bullet";

    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
    shapeDef.m_radius = radius;
}

ProjectileFactory::~ProjectileFactory()
{
    //dtor
}

Entity* ProjectileFactory::useFactory(FactoryParameters* parameters)
{
    //PositionVelocityParameters* params = (PositionVelocityParameters*)parameters;
    bodyDef.position = parameters->getVec2f("");// params->position;
    bodyDef.linearVelocity = parameters->getVec2f("v");//params->velocity;
    Entity* entity = new Projectile(explosion, new StaticSkin(radius,radius));
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);
    setMaterial(entity->mSkin,material);
    return entity;
}
