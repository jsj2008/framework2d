#include "JointBodyPartFactory.h"
#include <Physics/PhysicsManager.h>
#include <Physics/BodyParts/JointBodyPart.h>
#include <Physics/BodyParts/b2BodyBodyPart.h>

JointBodyPartFactory::JointBodyPartFactory()
{
    //ctor
    world = nullptr;
}

JointBodyPartFactory::~JointBodyPartFactory()
{
    //dtor
}

void JointBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    world = _factories->getWorld();
}
BodyPart* JointBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    BodyPart* bodyA = _parameters->get<BodyPart*>("bodyA", nullptr);
    BodyPart* bodyB = _parameters->get<BodyPart*>("bodyB", nullptr);
    assert(bodyA && bodyB);
    assert(dynamic_cast<b2BodyBodyPart*>(bodyA) && dynamic_cast<b2BodyBodyPart*>(bodyB));
    jointDef.bodyA = static_cast<b2BodyBodyPart*>(bodyA)->getBody();
    jointDef.bodyB = static_cast<b2BodyBodyPart*>(bodyB)->getBody();
    b2RevoluteJoint* joint = world->createJoint(&jointDef);
    BodyPart* bodyPart = new JointBodyPart(joint);
    return bodyPart;
}
