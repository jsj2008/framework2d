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
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    if (impulse->normalImpulses[0] > 50)
    {
        ((Entity*)bodyA->GetUserData())->damage();
    }
}
