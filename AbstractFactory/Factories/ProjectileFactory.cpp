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
    explosionFactory = loader->getFactory<Entity>("explosion","ExplosionFactory");
    skinFactory = loader->getFactory<Skin>("skin", "StaticSkinFactory");
    physicsManager = factories->getWorld();
}

ProjectileFactory::~ProjectileFactory()
{
    //dtor
}

Entity* ProjectileFactory::useFactory(FactoryParameters* parameters)
{
    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));
    bodyDef.linearVelocity = parameters->get<Vec2f>("velocity",Vec2f(1,0));
    Skin* skin = skinFactory->use(parameters);

    Entity* entity = new Projectile(explosionFactory, skin);
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&fixtureDef);
    return entity;
}
