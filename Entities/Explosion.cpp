#include "Explosion.h"
#include <Box2D/Box2D.h>
#include <Timer.h>
#include <Physics/PhysicsManager.h>

Explosion::Explosion(float _radius, float _damage, float _force, unsigned short _frames, Skin* _skin)
:Entity(_skin)
{
    //ctor
    radius = _radius;
    damage = _damage;
    force = _force;
    expiryFrame = _frames + g_Timer.getFrame();
}

Explosion::~Explosion()
{
    //dtor
}

void Explosion::update()
{
    b2Fixture* myFixture = mBody->GetFixtureList();
    Vec2f myPosition = mBody->GetWorldCenter();
    for (b2ContactEdge* ce = mBody->GetContactList(); ce != nullptr; ce = ce->next)
    {
        b2Contact* c = ce->contact;
        b2Fixture* fixture = c->GetFixtureA();
        if (fixture == myFixture)
        {
            fixture = c->GetFixtureB();
        }
        b2Body* body = fixture->GetBody();
        Vec2f point(body->GetWorldCenter());
        body->ApplyLinearImpulse((point-myPosition)*force,body->GetWorldCenter());
    }
    if (expiryFrame == g_Timer.getFrame())
    {
        g_PhysicsManager.destroyBody(mBody);
    }
}
