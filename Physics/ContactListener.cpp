#include "ContactListener.h"
#include <Entities/Entity.h>
#include <Physics/CollisionHandlers/AllCollisionHandlers.h>
#include <cstring>

ContactListener::ContactListener()
{
    //ctor
    memset(handlers,0,sizeof(CollisionHandler*)*eEntityTypeMax*eEntityTypeMax);
    CollisionHandler* noResponseHandler = new NoResponseHandler;
    for (unsigned int i = 0; i < eEntityTypeMax; i++)
    {
        for (unsigned int ii = i; ii < eEntityTypeMax; ii++)
        {
            handlers[i][ii] = noResponseHandler;
        }
    }
    CollisionHandler* wildcardProjectileHandler = new WildcardProjectileCollisionHandler;
    for (unsigned int i = 0; i < eEntityTypeMax; i++)
    {
        handlers[i][eProjectileEntityType] = wildcardProjectileHandler;
    }
    handlers[eStaticGeometryEntityType][eAIEntityType] = new StaticGeometryAIEntityCollisionHandler;
    handlers[eAIEntityType][eProjectileEntityType] = new AIEntityProjectileCollisionHandler;
}

ContactListener::~ContactListener()
{
    //dtor
}
#include <iostream>
using namespace std;
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    float totalImpulse = impulse->normalImpulses[0];
    if (contact->GetManifold()->pointCount == 2)
    {
        totalImpulse += impulse->normalImpulses[1];
    }
    if (totalImpulse > 1)
    {
        Entity* a = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
        Entity* b = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
        if (a != NULL && b != NULL) /// FIXME
            {
            if (a->getType() > b->getType())
            {
                Entity* c = b;
                b = a;
                a = c;
            }
            HighVelocityImpact impact(a,b,totalImpulse);
            highVelocityImpacts.push(impact);
        }
    }
}

void ContactListener::process()
{
    while (!highVelocityImpacts.empty())
    {
        HighVelocityImpact impact = highVelocityImpacts.front();
        handlers[impact.entityA->getType()][impact.entityB->getType()]->handle(impact.entityA,impact.entityB,impact.totalImpulse);
        highVelocityImpacts.pop();
    }
}
