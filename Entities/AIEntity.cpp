#include "AIEntity.h"
#include <AI/Brain.h>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>
#include <Factory/ParticleDef.h>
#include <Factory/FactoryList.h>
#include <cassert>
#define JUMP_IMPULSE -1.0f*WORLD_GRAVITY

AIEntity::AIEntity(Brain* _Brain)
{
    //ctor
    mBrain = _Brain;
    mBrain->setEntity(this);
    grounded = false;
    health = 100;
}

AIEntity::~AIEntity()
{
    //dtor
    delete mBrain;
}
void AIEntity::damage()
{
    ParticleDef def;
    def.density = 1.0f;
    def.lifetime = 100;
    def.setMaterial("Spark");
    def.setPosition(mBody->GetPosition());
    g_FactoryList.useFactory(def,eParticleFactory);
}
void AIEntity::update()
{
#ifdef JUMPING
    for (b2ContactEdge* ce = mBody->GetContactList(); ce; ce = ce->next)
    {
        b2Contact* contact = ce->contact;
        b2WorldManifold manifold;
        contact->GetWorldManifold(&manifold);
        float dot = b2Dot(manifold.normal,Vec2f(0,1));
        if (dot > 0.8f) // Close enough to a floor
        {
            grounded = true;
            groundNormal = manifold.normal;
            groundNormal.x /= 10.0f;
            groundNormal.y /= 10.0f;
            float t = groundNormal.x;
            groundNormal.x = groundNormal.y;
            groundNormal.y = -t;
            break;
        }
    }
    if (health  < 0)
    {
        g_PhysicsManager.destroyBody(mBody);
    }
#endif
}
void AIEntity::jump()
{
    if (grounded)
    {
        Vec2f point(0,0);
        point = mBody->GetWorldCenter();
        mBody->ApplyLinearImpulse(Vec2f(0.0,JUMP_IMPULSE), point);
        grounded = false;
    }
}
void AIEntity::walkLeft()
{
    Vec2f point(0,0);
    point = mBody->GetWorldCenter();
    mBody->ApplyLinearImpulse(Vec2f(-1,0), point);
}

void AIEntity::walkRight()
{
    Vec2f point(0,0);
    point = mBody->GetWorldCenter();
    mBody->ApplyLinearImpulse(Vec2f(1,0), point);
}














