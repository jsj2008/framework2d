#include "CharacterBodyFactory.h"
<<<<<<< HEAD
#include <Physics/BodyParts/BodyPart.h>
=======
#include <Physics/BodyPart.h>
>>>>>>> FETCH_HEAD
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>

CharacterBodyFactory::CharacterBodyFactory()
{
    //ctor
}
CharacterBodyFactory::~CharacterBodyFactory()
{
    //dtor
}

void CharacterBodyFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    bodyFactory = loader->getFactory<BodyPart>("body", "SingleFixtureBodyPartFactory");
    wheelFactory = loader->getFactory<BodyPart>("wheel", "SingleFixtureBodyPartFactory");
<<<<<<< HEAD
    jointFactory = loader->getFactory<BodyPart>("joint", "JointBodyPartFactory");
=======
    jointFactory = loader->getFactory<BodyPart>("joint", "SingleFixtureBodyPartFactory");
>>>>>>> FETCH_HEAD
}

BodyPart* CharacterBodyFactory::useFactory(FactoryParameters* _parameters)
{
    BodyPart* body = bodyFactory->use(_parameters, nullptr);
    BodyPart* wheel = wheelFactory->use(_parameters, body);
    _parameters->add<BodyPart*>("bodyA", body);
    _parameters->add<BodyPart*>("bodyB", wheel);
    BodyPart* joint = jointFactory->use(_parameters, wheel);
<<<<<<< HEAD
    _parameters->add<BodyPart*>("joint", joint);
=======
>>>>>>> FETCH_HEAD
    return body;
}
