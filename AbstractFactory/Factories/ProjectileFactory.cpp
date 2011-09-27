#include "ProjectileFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Projectile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ProjectileFactory::ProjectileFactory()
{
    physicsManager = nullptr;
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
}
void ProjectileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    expiryTime = loader->get<float>("expiryTime",10.0f);
    radius = loader->get<float>("radius",1.0f);
    shapeDef.m_radius = radius; /// FIXME just spotted this
    explosion = loader->get<std::string>("explosion","ExplosionFactory");
    material = loader->get<std::string>("material","Bullet");
    physicsManager = factories->getWorld();
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
    Skin* skin = new StaticSkin(radius,radius);
    Entity* entity = new Projectile(explosion, skin);
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);
    setMaterial(skin,material);
    return entity;
}
