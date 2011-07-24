#include "PhysicsParticle.h"
#include <Physics/PhysicsManager.h>

PhysicsParticle::PhysicsParticle(int _timer, Skin* _skin)
:Entity(_skin)
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
        g_PhysicsManager.destroyBody(mBody);
    }
}
