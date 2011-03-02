#include "ParticleFactory.h"
#include <Factory/ParticleDef.h>
#include <Entities/PhysicsParticle.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>

ParticleFactory::ParticleFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    shape.m_radius = 0.1;
}

ParticleFactory::~ParticleFactory()
{
    //dtor
}

Entity* ParticleFactory::createEntity(FactoryDef* def)
{
    Entity* entity = new PhysicsParticle;

    bodyDef.position = def->getPosition();
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&shape, 1.0f);

    entity->mSkin = new StaticSkin(1.0f,1.f);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(def->materialName));
    return entity;
}
