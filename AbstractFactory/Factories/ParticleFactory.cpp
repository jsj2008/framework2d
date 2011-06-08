#include "ParticleFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/PhysicsParticle.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ParticleFactory::ParticleFactory(FactoryLoader* loader)
{
    //ctor
    density = loader->get<float>("density",1.0f);
    lifetime = loader->get<int>("lifetime",60); /// FIXME needs ints
    materialName = loader->get<std::string>("materialName","Spark");
    bodyDef.type = b2_dynamicBody;

}

ParticleFactory::~ParticleFactory()
{
    //dtor
}
Entity* ParticleFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Entity* entity = new PhysicsParticle(lifetime);

    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));//params->position;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&shape, density);

    entity->mSkin = new StaticSkin(1.0f,1.f);
    setMaterial(entity->mSkin,materialName);
    return entity;
}
