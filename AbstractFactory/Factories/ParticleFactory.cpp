#include "ParticleFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/PhysicsParticle.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>

ParticleFactory::ParticleFactory(float _density, int _lifetime)
{
    //ctor
    density = _density;
    lifetime = _lifetime;
    materialName = "Spark";
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

    bodyDef.position = parameters->getVec2f("");//params->position;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&shape, density);

    entity->mSkin = new StaticSkin(1.0f,1.f);
    setMaterial(entity->mSkin,materialName);
    return entity;
}
