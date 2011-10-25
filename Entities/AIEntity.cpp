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
void AIEntity::weaponBegin(Vec2f targetPosition)
{

}
void AIEntity::weaponMove(Vec2f targetPosition)
{

}
void AIEntity::weaponEnd(Vec2f targetPosition)
{
    weapon->fireEnd(mBody->GetPosition(),targetPosition);
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













