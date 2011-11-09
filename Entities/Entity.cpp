#include "Entity.h"
#include <Graphics/Skins/Skin.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Physics/Body.h>
#include <Physics/PhysicsManager.h>

Entity::Entity(Skin* _skin)
{
    //ctor
    mSkin = _skin;
    body = nullptr;
}

Entity::~Entity()
{
    //dtor
    delete mSkin;
    delete body;
}

void Entity::render()
{
    mSkin->render(body);
}

void Entity::setBody(Body* _body)
{
    assert(body == nullptr);
    body = _body;
}
const Vec2f& Entity::getPosition()
{
    return body->getPosition();
}

void Entity::registerActions()
{

}
