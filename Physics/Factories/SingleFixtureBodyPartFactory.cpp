#include "SingleFixtureBodyPartFactory.h"
#include <Physics/PhysicsManager.h>
#include <Physics/SingleFixtureBodyPart.h>

SingleFixtureBodyPartFactory::SingleFixtureBodyPartFactory()
{
    //ctor
}

SingleFixtureBodyPartFactory::~SingleFixtureBodyPartFactory()
{
    //dtor
}

void SingleFixtureBodyPartFactory::init(FactoryLoader* _loader, AbstractFactories* _factories)
{
    physicsManager = _factories->getWorld();

    bodyDef.bullet = _loader->get<bool>("bullet", false);
    bodyDef.fixedRotation = _loader->get<bool>("fixedRotation", false);
    bodyDef.type = _loader->get<int>("bodyType", b2_staticBody); /// FIXME loader needs to accept enums

    responseFactory = _loader->getFactory<CollisionResponse>("collisionResponse", "CollisionResponseFactory");
    fixtureDef.density = _loader->get<float>("density", 1.0f);
    fixtureDef.restitution = _loader->get<float>("restitution", 1.0f);
    shapeFactory = _loader->getFactory<b2Shape>("shape", "ShapeFactory");
}

BodyPart* SingleFixtureBodyPartFactory::useFactory(FactoryParameters* _parameters)
{
    bodyDef.position = _parameters->get<Vec2f>("position", {0,0});
    bodyDef.linearVelocity = _parameters->get<Vec2f>("velocity",{0,0});
    SingleFixtureBodyPart* bodyPart = new SingleFixtureBodyPart;
    bodyDef.bodyPart = bodyPart;
    b2Body* body = physicsManager->createBody(&bodyDef);

    fixtureDef.filter.response = responseFactory->use(_parameters, bodyPart);
    fixtureDef.shape = shapeFactory->use(_parameters, bodyPart);

    bodyPart->setBody(body);
    fixtureDef.bodyPart = bodyPart;
    bodyPart->setFixture(body->CreateFixture(&fixtureDef));

    delete fixtureDef.shape; /// FIXME override the box2d factory for efficiency

    return bodyPart;
}
