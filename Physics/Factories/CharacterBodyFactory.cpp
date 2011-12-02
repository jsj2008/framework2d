#include "CharacterBodyFactory.h"
#include <Physics/Body.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>

CharacterBodyFactory::CharacterBodyFactory()
{

}
void CharacterBodyFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    world = factories->getWorld();
    dimensions = loader->get<Vec2f>("dimensions",Vec2f(2,2));

    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    fixtureDef.shape = &shapeDef;
    fixtureDef.density = 1.0f;

    wheelBody.type = b2_dynamicBody;
    wheelBody.userData = nullptr;
    wheelFixture.shape = &wheelShape;
    wheelFixture.density = 1.0f;
    wheelFixture.friction = 50.0f;
    wheelShape.m_radius = 0.5f;

    wheelJoint.collideConnected = false;
    wheelJoint.maxMotorTorque = 50.0f;
    wheelJoint.enableMotor = true;

    collisionResponse = loader->getFactory<CollisionResponse>("collisionResponse", "CollisionResponseFactory");
}

CharacterBodyFactory::~CharacterBodyFactory()
{
    //dtor
}

Body* CharacterBodyFactory::useFactory(FactoryParameters* parameters)
{
    Vec2f position = parameters->get<Vec2f>("position",Vec2f(0,0));
    Vec2f anchorPoint(dimensions.x*0.1f,dimensions.y*0.33f);
    anchorPoint += position;

    bodyDef.position = position;
    bodyDef.position.x += dimensions.x*0.1f;
    shapeDef.SetAsBox(dimensions.x*0.4f,dimensions.y*0.33f);
    bodyDef.userData = parameters->get<void*>("userData",nullptr);
    Body* body = world->createBody(&bodyDef);
    wheelFixture.filter.response = fixtureDef.filter.response = collisionResponse->use(parameters);
    body->createFixture(&fixtureDef);

    wheelBody.position = position;
    wheelBody.position += Vec2f(dimensions.x*0.1f,dimensions.y*0.33f);
    Body* wheel = world->createBody(&wheelBody);
    wheel->createFixture(&wheelFixture);

    wheelJoint.Initialize(body->getBody(),wheel->getBody(),anchorPoint);
    b2Joint* joint = world->createJoint(&wheelJoint);

    parameters->add<void*>("joint",(void*)joint);

    return body;
}
