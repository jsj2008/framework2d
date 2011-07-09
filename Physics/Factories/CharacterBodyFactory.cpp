#include "CharacterBodyFactory.h"
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/FactoryLoader.h>
#include <AbstractFactory/FactoryParameters.h>

CharacterBodyFactory::CharacterBodyFactory()
{

}
void CharacterBodyFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    dimensions = loader->get<Vec2f>("dimensions",Vec2f(2,2));

    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    fixtureDef.shape = &shapeDef;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = PhysicsManager::EnemyCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::EnemyCategory);

    wheelBody.type = b2_dynamicBody;
    wheelBody.userData = nullptr;
    wheelFixture.shape = &wheelShape;
    wheelFixture.density = 1.0f;
    wheelFixture.friction = 50.0f;
    wheelFixture.filter.categoryBits = PhysicsManager::PlayerCategory;
    wheelFixture.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::PlayerCategory);
    wheelShape.m_radius = 0.5f;

    wheelJoint.collideConnected = false;
    wheelJoint.maxMotorTorque = 50.0f;
    wheelJoint.enableMotor = true;
}

CharacterBodyFactory::~CharacterBodyFactory()
{
    //dtor
}

b2Body* CharacterBodyFactory::useFactory(FactoryParameters* parameters)
{
    Vec2f position = parameters->get<Vec2f>("position",Vec2f(0,0));
    Vec2f anchorPoint(dimensions.x*0.1f,dimensions.y*0.33f);
    anchorPoint += position;

    int collisionGroup = g_PhysicsManager.getNextNegativeCollisionGroup();
    fixtureDef.filter.groupIndex = collisionGroup;
    wheelFixture.filter.groupIndex = collisionGroup;

    bodyDef.position = position;
    bodyDef.position.x += dimensions.x*0.1f;
    shapeDef.SetAsBox(dimensions.x*0.4f,dimensions.y*0.33f);
    bodyDef.userData = parameters->get<void*>("userData",nullptr);
    b2Body* body = g_PhysicsManager.createBody(&bodyDef);
    body->CreateFixture(&fixtureDef);

    wheelBody.position = position;
    wheelBody.position += Vec2f(dimensions.x*0.1f,dimensions.y*0.33f);
    b2Body* wheel = g_PhysicsManager.createBody(&wheelBody);
    wheel->CreateFixture(&wheelFixture);

    wheelJoint.Initialize(body,wheel,anchorPoint);
    b2Joint* joint = g_PhysicsManager.createJoint(&wheelJoint);

    parameters->add<void*>("joint",(void*)joint);

    return body;
}
