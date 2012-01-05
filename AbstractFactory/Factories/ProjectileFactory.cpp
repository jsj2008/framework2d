#include "ProjectileFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Projectile.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Physics/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Entities/CollisionDatabase.h>

ProjectileFactory::ProjectileFactory()
{
}
void ProjectileFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    expiryTime = loader->get<float>("expiryTime",10.0f);
    radius = loader->get<float>("radius",1.0f);
    explosionFactory = loader->getFactory<Entity>("explosion","ExplosionFactory");
    skinFactory = loader->getFactory<Skin>("skins", "StaticSkinFactory");
    assert(skinFactory);



}

ProjectileFactory::~ProjectileFactory()
{
    //dtor
}

Entity* ProjectileFactory::useFactory(FactoryParameters* _parameters)
{
    assert(skinFactory);
    Entity* entity = new Projectile(explosionFactory);
    entity->baseInit(skinFactory->use(_parameters, entity));

    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);


    return entity;
}
