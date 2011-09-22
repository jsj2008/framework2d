#include "Entity.h"
#include <Graphics/Skins/Skin.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>

Entity::Entity(Skin* _skin)
{
    //ctor
    mSkin = _skin;
    mBody = nullptr;
}

Entity::~Entity()
{
    //dtor
    EntityDeathEvent event(this);
    deathHandler.trigger(&event);
    delete mSkin;
    mBody->GetWorld()->DestroyBody(mBody);
}

void Entity::render()
{
    mSkin->render(mBody);
}

void Entity::setBody(b2Body* _body)
{
    assert(mBody == nullptr);
    mBody = _body;
}
const Vec2f& Entity::getPosition()
{
    return mBody->GetPosition();
}

void Entity::registerDeathListener(EventsListener<EntityDeathEvent>* _listener)
{
    deathHandler.registerListener(_listener, {eClearQueue|eBlockQueue});
}
