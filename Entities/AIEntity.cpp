#include "AIEntity.h"
#include <AI/Brain.h>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>
#include <Factory/ParticleDef.h>
#include <Factory/FactoryList.h>
#include <Factory/ProjectileDef.h>
#include <cassert>
#define JUMP_IMPULSE -5.0f*WORLD_GRAVITY

AIEntity::AIEntity(Brain* _Brain)
{
    //ctor
    mBrain = _Brain;
    wheel = NULL;
    mBrain->setEntity(this);
    grounded = false;
    health = 15;
}

AIEntity::~AIEntity()
{
    //dtor
    delete mBrain;
}
void AIEntity::fireAt(Vec2f targetPosition)
{
    Vec2f direction = targetPosition - mBody->GetPosition();
    direction /= direction.Length();
    fire(direction);
}
void AIEntity::fire(Vec2f targetDirection)
{
    ProjectileDef def;
    Vec2f position = mBody->GetPosition();
    position += targetDirection*3;
    def.set("Bullet",1.0f,position,targetDirection*30.0f);
    g_FactoryList.useFactory(def,eProjectileFactory);
}
void AIEntity::damage()
{
    ParticleDef def;
    def.density = 1.0f;
    def.lifetime = 100;
    def.setMaterial("Spark");
    def.setPosition(mBody->GetPosition());
    g_FactoryList.useFactory(def,eParticleFactory);

    health--;
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
#endif
    mBrain->update();
    if (health  < 1)
    {
        g_PhysicsManager.destroyBody(mBody);
    }
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
    if (wheel == NULL)
    {
        Vec2f point(0,0);
        point = mBody->GetWorldCenter();
        mBody->ApplyLinearImpulse(Vec2f(-0.2,0), point);
    }
    else
    {
        wheel->SetMotorSpeed(-20.0f);
    }
}

void AIEntity::walkRight()
{
    if (wheel == NULL)
    {
        Vec2f point(0,0);
        point = mBody->GetWorldCenter();
        mBody->ApplyLinearImpulse(Vec2f(0.2,0), point);
    }
    else
    {
        wheel->SetMotorSpeed(20.0f);
    }
}














