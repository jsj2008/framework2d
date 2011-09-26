#include "AIEntity.h"
#include <AI/Brain.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Weapons/Weapon.h>
#include <AI/CharacterController.h>
#include <cassert>
#define JUMP_IMPULSE -0.5f*WORLD_GRAVITY

AIEntity::AIEntity(Brain* _Brain, Weapon* _weapon, AbstractFactoryBase<Entity>* _damageSprayFactory, Skin* _skin)
:Entity(_skin),
controller(nullptr)
{
    //ctor
    mBrain = _Brain;
    weapon = _weapon;
    mBrain->setEntity(this);
    health = 2;
    damageSprayFactory = _damageSprayFactory;
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
    /*ProjectileDef def;
    Vec2f position = mBody->GetPosition();
    position += targetDirection*3;
    def.set("Bullet",1.0f,position,targetDirection*30.0f);
    g_FactoryList.useFactory(def,eProjectileFactory);*/
    weapon->fire(mBody->GetPosition(),targetDirection);
}
void AIEntity::damage()
{
    /*ParticleDef def;
    def.density = 1.0f;
    def.lifetime = 100;
    def.setMaterial("Spark");
    def.position = mBody->GetPosition();
    g_FactoryList.useFactory(def,eParticleFactory);*/
    FactoryParameters parameters({{"position",mBody->GetPosition()}});
    damageSprayFactory->use(&parameters);
    health--;
}
void AIEntity::update()
{
    mBrain->update();
    if (health  < 1)
    {
        mBody->GetWorld()->DestroyBody(mBody);
    }
    controller->update();
}
void AIEntity::jump()
{
    controller->jump();
}
void AIEntity::walkLeft()
{
    controller->walkLeft();
}
void AIEntity::walkRight()
{
    controller->walkRight();
}
void AIEntity::stopWalking()
{
    controller->stopWalking();
}













