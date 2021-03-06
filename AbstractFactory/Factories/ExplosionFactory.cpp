#include "ExplosionFactory.h"
#include <Entities/Explosion.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <AbstractFactory/FactoryParameters.h>

#include <Physics/BodyParts/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>

ExplosionFactory::ExplosionFactory()
{
}
void ExplosionFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    damage = loader->get<float>("damage",0.0f);
    force = loader->get<float>("force",2.0f);
    time = loader->get<float>("time",10.0f);
    radius = loader->get<float>("radius",1.0f);
    bodyFactory = loader->getFactory<BodyPart>("body", "b2FixtureBodyPartFactory");

    skinFactory = loader->getFactory<Skin>("skin", "BubbleSkinFactory");
}

ExplosionFactory::~ExplosionFactory()
{
    //dtor
}
Entity* ExplosionFactory::useFactory(FactoryParameters* _parameters)
{
    Entity* entity = new Explosion(radius,damage,force,time);
    entity->baseInit(skinFactory->use(_parameters, entity));
    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);
    return entity;
}
