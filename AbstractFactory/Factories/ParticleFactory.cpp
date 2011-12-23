#include "ParticleFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/PhysicsParticle.h>
#include <Physics/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ParticleFactory::ParticleFactory()
{


}
void ParticleFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    density = loader->get<float>("density",1.0f);
    lifetime = loader->get<int>("lifetime",60); /// FIXME needs ints
    skinFactory = loader->getFactory<Skin>("skin", "StaticSkinFactory");

}

ParticleFactory::~ParticleFactory()
{
    //dtor
}
Entity* ParticleFactory::useFactory(FactoryParameters* _parameters)
{
    Entity* entity = new PhysicsParticle(lifetime);
    entity->baseInit(skinFactory->use(_parameters, entity));

    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);


    return entity;
}
