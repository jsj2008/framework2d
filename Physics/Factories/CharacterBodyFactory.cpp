#include "CharacterBodyFactory.h"
#include <Physics/BodyParts/BodyPart.h>
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
    bodyFactory = loader->getFactory<BodyPart>("body", "b2FixtureBodyPartFactory");
    wheelFactory = loader->getFactory<BodyPart>("wheel", "b2FixtureBodyPartFactory");
    jointFactory = loader->getFactory<BodyPart>("joint", "JointBodyPartFactory");
}

BodyPart* CharacterBodyFactory::useFactory(FactoryParameters* _parameters)
{
    BodyPart* body = bodyFactory->use(_parameters, nullptr);
    BodyPart* wheel = wheelFactory->use(_parameters, body);
    _parameters->add<BodyPart*>("bodyA", body);
    _parameters->add<BodyPart*>("bodyB", wheel);
    BodyPart* joint = jointFactory->use(_parameters, wheel);
    _parameters->add<BodyPart*>("joint", joint);
    return body;
}
