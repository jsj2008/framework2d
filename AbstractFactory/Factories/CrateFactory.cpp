#include "CrateFactory.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Physics/PhysicsManager.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Entities/Crate.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AbstractFactory/FactoryLoader.h>
#include <Entities/CollisionDatabase.h>

CrateFactory::CrateFactory()
{
    //ctor
}

CrateFactory::~CrateFactory()
{
    //dtor
}

void CrateFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    skinFactory = loader->getFactory<Skin>("skin","StaticSkinFactory");
    bodyFactory = loader->getFactory<BodyPart>("body", "b2FixtureBodyPartFactory");
    //
}
Entity* CrateFactory::useFactory(FactoryParameters* _parameters)
{
    Entity* entity = new Crate;
    entity->baseInit(skinFactory->use(_parameters, entity));

    BodyPart* body = bodyFactory->use(_parameters, entity);
    entity->setRootBody(body);

    return entity;
}
