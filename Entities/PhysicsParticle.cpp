#include "PhysicsParticle.h"
#include <Physics/PhysicsManager.h>

PhysicsParticle::PhysicsParticle(int _timer)
{
    //ctor
    timer = _timer;
}

PhysicsParticle::~PhysicsParticle()
{
    //dtor
}

void PhysicsParticle::update()
{
    timer--;
    if (timer == 0)
    {
        delete this;
    }
}
