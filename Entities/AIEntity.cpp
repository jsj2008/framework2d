#include "AIEntity.h"
#include <AI/Brain.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Weapons/Weapon.h>
#include <AI/CharacterController.h>
#include <cassert>
#define JUMP_IMPULSE -0.5f*WORLD_GRAVITY

AIEntity::AIEntity()
:controller(nullptr)
{
    //ctor
    mBrain = nullptr;
    weapon = nullptr;
    health = 2;
    damageSprayFactory = nullptr;
}

void AIEntity::init(Brain* _Brain, Weapon* _weapon, AbstractFactoryBase<Entity>* _damageSprayFactory, Skin* _skin)
{
    assert(!mBrain);
    mBrain = _Brain;
    weapon = _weapon;
    mBrain->setEntity(this);
    damageSprayFactory = _damageSprayFactory;
    baseInit(_skin);
}

AIEntity::~AIEntity()
{
    //dtor
    delete mBrain;
}
void AIEntity::setController(CharacterController* _controller)
{
    controller = _controller;
    controller->setAIEntity(this);
}
void AIEntity::weaponBegin(Vec2f targetPosition)
{

}
void AIEntity::weaponMove(Vec2f targetPosition)
{

}
void AIEntity::weaponEnd(Vec2f targetPosition)
{
    weapon->fireEnd(rootBody->getPosition(),targetPosition);
}
void AIEntity::damage()
{
    FactoryParameters _parameters;
    _parameters.add<Vec2f>("position", rootBody->getPosition());
    damageSprayFactory->use(&_parameters, nullptr);
    health--;
}
void AIEntity::update()
{
    mBrain->update();
    if (health  < 1)
    {
        delete rootBody; /// FIXME delete this
    }
    controller->update();
}













