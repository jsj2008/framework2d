#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <SDL/SDL_timer.h>

PhysicsManager::PhysicsManager()
{
    //ctor
    mWorld = new b2World(b2Vec2(0,1),true);
    startTime = SDL_GetTicks();
    stepsTaken = 0;
}

PhysicsManager::~PhysicsManager()
{
    //dtor
}

b2Body* PhysicsManager::bodyFactory(PhysicsFactoryDef& def, b2Vec2& initialPosition, void* userData)
{
    def.bodyDef.userData = userData;
    def.bodyDef.position = initialPosition;
    b2Body* body = mWorld->CreateBody(&(def.bodyDef));
    //def.fixtureDef.userData = userData;
    //def.fixtureDef.shape = &def.fixtureShape;
    body->CreateFixture(&def.shape, def.density);
    return body;
}

void PhysicsManager::update()
{
    unsigned int currentTime = SDL_GetTicks();
    unsigned int totalTimePassed = currentTime - startTime;
    unsigned int stepsToTake = totalTimePassed/60;
    if (stepsToTake > stepsTaken)
    {
        float timestep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        mWorld->Step(timestep, velocityIterations, positionIterations);
    }
}
