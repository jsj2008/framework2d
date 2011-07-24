#include "ParticleFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/PhysicsParticle.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ParticleFactory::ParticleFactory()
{
    bodyDef.type = b2_dynamicBody;
}
void ParticleFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    density = loader->get<float>("density",1.0f);
    lifetime = loader->get<int>("lifetime",60); /// FIXME needs ints
    materialName = loader->get<std::string>("materialName","Spark");

}

ParticleFactory::~ParticleFactory()
{
    //dtor
}
Entity* ParticleFactory::useFactory(FactoryParameters* parameters)
{
    //PositionParameters* params = (PositionParameters*)parameters;
    Skin* skin = new StaticSkin(1.0f,1.f);
    Entity* entity = new PhysicsParticle(lifetime, skin);

    bodyDef.position = parameters->get<Vec2f>("position",Vec2f(0,0));//params->position;
    bodyDef.userData = (void*)entity;
    b2Body* body = g_PhysicsManager.createBody(&bodyDef);
    entity->setBody(body);
    body->CreateFixture(&shape, density);

    setMaterial(skin,materialName);
    return entity;
}
