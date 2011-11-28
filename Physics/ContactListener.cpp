#include "ContactListener.h"
#include <Entities/Entity.h>
#include <Entities/CollisionResponse.h>
#include <Physics/CollisionObject.h>
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
void ContactListener::BeginContact(b2Contact* contact)
{
    CollisionResponse* a = static_cast<CollisionResponse*>(contact->GetFixtureA()->GetUserData());
    CollisionResponse* b = static_cast<CollisionResponse*>(contact->GetFixtureB()->GetUserData());
    if (a != nullptr && b != nullptr)
    {
        //collidedFixtures.push({contact->GetFixtureA(), contact->GetFixtureB()});
    }
}
void ContactListener::EndContact(b2Contact* contact)
{

}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    CollisionResponse* rA = static_cast<CollisionResponse*>(a->GetUserData());
    CollisionResponse* rB = static_cast<CollisionResponse*>(b->GetUserData());

    if (rA != nullptr && rB != nullptr)
    {
        CollisionObject cA(a, b);
        CollisionObject cB(b, a);
        rA->collide(&cA);
        rB->collide(&cB);
    }
}

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
        if (a != nullptr && b != nullptr) /// FIXME
        {
            if (a->getType() > b->getType())
            {
                Entity* c = b;
                b = a;
                a = c;
            }
            HighVelocityImpact impact(a,b,totalImpulse);
            //highVelocityImpacts.push(impact);
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
    /*while (!collidedFixtures.empty())
    {
        b2Fixture* fixtureA = collidedFixtures.top().first;
        b2Fixture* fixtureB = collidedFixtures.top().second;
        CollisionResponse* a = static_cast<CollisionResponse*>(fixtureA->GetUserData());
        CollisionResponse* b = static_cast<CollisionResponse*>(fixtureB->GetUserData());
        a->collide(b->getCategory(), fixtureA, fixtureB);
        b->collide(a->getCategory(), fixtureB, fixtureA);
        collidedFixtures.pop();
    }*/
}
