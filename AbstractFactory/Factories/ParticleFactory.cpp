#include "ParticleFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/PhysicsParticle.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ParticleFactory::ParticleFactory()
{
    physicsManager = nullptr;
    bodyDef.type = b2_dynamicBody;
}
void ParticleFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    density = loader->get<float>("density",1.0f);
    lifetime = loader->get<int>("lifetime",60); /// FIXME needs ints
    skinFactory = loader->getFactory<Skin>("skin", "StaticSkinFactory");
    physicsManager = factories->getWorld();
}

ParticleFactory::~ParticleFactory()
{
    //dtor
}
Entity* ParticleFactory::useFactory(FactoryParameters* parameters)
{
    Skin* skin = skinFactory->use(parameters);
    Entity* entity = new PhysicsParticle(lifetime, skin);

    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));
    bodyDef.userData = (void*)entity;
    b2Body* body = physicsManager->createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&shape, density);

    return entity;
}
