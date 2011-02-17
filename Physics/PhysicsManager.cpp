#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <Timer.h>

PhysicsFactoryDef::PhysicsFactoryDef()
{
    density = 1.0f;
#ifdef JUMPING_SENSOR
    useAdditionalFixture = false;
#endif
}
PhysicsManager::PhysicsManager()
{
    //ctor
    mWorld = new b2World(b2Vec2(0,WORLD_GRAVITY),true);
    stepsTaken = 0;
}

PhysicsManager::~PhysicsManager()
{
    //dtor
}
void PhysicsManager::init()
{
    startTime = g_Timer.getTicks();
}
b2Body* PhysicsManager::bodyFactory(PhysicsFactoryDef& def, b2Vec2& initialPosition, void* userData)
{
    def.bodyDef.userData = userData;
    def.bodyDef.position = initialPosition;
    b2Body* body = mWorld->CreateBody(&(def.bodyDef));
    body->CreateFixture(&def.shape, def.density);
#ifdef JUMPING_SENSOR
    if (def.useAdditionalFixture)
    {
        body->CreateFixture(&def.additionalFixture);
    }
#endif
    return body;
}
bool PhysicsManager::update()
{
    unsigned int currentTime = g_Timer.getTicks();
    unsigned int totalTimePassed = currentTime - startTime;
    unsigned int stepsToTake = (totalTimePassed*60)/1000;
    if (stepsToTake > stepsTaken)
    {
        float timestep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        mWorld->Step(timestep, velocityIterations, positionIterations);
        return true;
    }
    else return false;
}
