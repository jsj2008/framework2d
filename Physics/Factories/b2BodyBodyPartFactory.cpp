#include "b2BodyBodyPartFactory.h"
#include <Physics/PhysicsManager.h>
#include <Physics/BodyParts/b2BodyBodyPart.h>

b2BodyBodyPartFactory::b2BodyBodyPartFactory()
{
    //ctor
}

b2BodyBodyPartFactory::~b2BodyBodyPartFactory()
{
    //dtor
}

void b2BodyBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    physicsManager = _factories->getWorld();

    bodyDef.bullet = _loader->get<bool>("bullet", false);
    bodyDef.fixedRotation = _loader->get<bool>("fixedRotation", false);
    bodyDef.type = _loader->get<int>("bodyType", b2_dynamicBody); /// FIXME loader needs to accept enums
}

BodyPart* b2BodyBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    bodyDef.position = _parameters->get<Vec2f>("position", {0,0});
    bodyDef.linearVelocity = _parameters->get<Vec2f>("velocity",{0,0});
    bodyDef.angle = _parameters->get<float>("rotation", 0.0f);
    bodyDef.angularVelocity = _parameters->get<float>("angularVelocity", 0.0f);

    b2Body* body = physicsManager->createBody(&bodyDef);
    b2BodyBodyPart* bodyPart = new b2BodyBodyPart(body);

    return bodyPart;
}
