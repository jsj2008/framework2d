#include "AIEntity.h"
#include <AI/Brain.h>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>
#include <Factory/ParticleDef.h>
#include <Factory/FactoryList.h>
#include <Factory/ProjectileDef.h>
#include <cassert>
#define JUMP_IMPULSE -0.5f*WORLD_GRAVITY

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
    mBrain->update();
    if (health  < 1)
    {
        g_PhysicsManager.destroyBody(mBody);
    }
    pogoStick->SetMotorSpeed(-10.0f);
}
#include <iostream>
void AIEntity::jump()
{
    /*if (grounded)
    {
        Vec2f point(0,0);
        point = mBody->GetWorldCenter();
        mBody->ApplyLinearImpulse(Vec2f(0.0,JUMP_IMPULSE), point);
        grounded = false;
    }*/
    pogoStick->SetMotorSpeed(100.0f);
    std::cout << "Jump" << std::endl;
}
void AIEntity::walkLeft()
{
    wheel->SetMotorSpeed(-20.0f);
}
void AIEntity::walkRight()
{
    wheel->SetMotorSpeed(20.0f);
}
void AIEntity::stopWalking()
{
    wheel->SetMotorSpeed(0.0f);
}













