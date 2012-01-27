#include "Entity.h"
#include <Graphics/Skins/Skin.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/PhysicsManager.h>
#include <Physics/CollisionObject.h>

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
    assert(_rootBody->getParent() == this);
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

void Entity::registerActions(GameObjectType* _type)
{
    type.createActionHandle("buoyancy", &Entity::floatationAction);
}

void Entity::floatationAction(CollisionObject* _object)
{
    BodyPart* other = _object->getOther();
    other->applyLinearImpulse(other->getLinearVelocity()*-0.1f);
    other->applyLinearImpulse(Vec2f(0, other->getAreaBelowLine(18.5f) * -1.0f * other->getDensity()));
    std::cout << "Floating " <<  _object->getOther()->getAreaBelowLine(18.5f) << std::endl;
    //_object->getOther()->getArea() << std::endl;
}
