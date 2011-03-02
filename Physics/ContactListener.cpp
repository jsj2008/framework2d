#include "ContactListener.h"
#include <Entities/Entity.h>

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}
#include <iostream>
using namespace std;
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    if (impulse->normalImpulses[0] > 50)
    {
        HighVelocityImpact impact;
        impact.entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
        impact.entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
        highVelocityImpacts.push(impact);
    }
}

void ContactListener::process()
{
    while (!highVelocityImpacts.empty())
    {
        HighVelocityImpact impact = highVelocityImpacts.front();
        impact.entityA->damage();
        impact.entityB->damage();
        highVelocityImpacts.pop();
    }
}
