#include "Entity.h"
#include <Graphics/Skins/Skin.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Physics/BodyPart.h>
#include <Physics/PhysicsManager.h>

Entity::Entity()
{
    rootBody = nullptr;
    mSkin = nullptr;
}

void Entity::baseInit(Skin* _skin)
{
    assert(!mSkin);
    mSkin = _skin;
}

Entity::~Entity()
{
    //dtor
    delete mSkin;
    delete rootBody;
}

void Entity::render()
{
    assert(mSkin);
    assert(rootBody);
    mSkin->render(rootBody);
}

void Entity::setRootBody(BodyPart* _rootBody)
{
    assert(rootBody == nullptr);
    rootBody = _rootBody;
}
BodyPart* Entity::getRootBody()
{
    return rootBody;
}
const Vec2f& Entity::getPosition()
{
    return rootBody->getPosition();
}

void Entity::registerActions()
{
    createActionHandle("Floatation", &Entity::floatationAction);
}

void Entity::floatationAction(CollisionObject* _object)
{
}
