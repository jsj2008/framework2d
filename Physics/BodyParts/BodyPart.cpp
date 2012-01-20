#include "BodyPart.h"
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>

BodyPart::BodyPart()
{
    //ctor
    fixture = nullptr;
}

BodyPart::~BodyPart()
{
    //dtor
}

void BodyPart::registerActions(GameObjectType* _type)
{

}

b2Body* BodyPart::getBody()
{
    return fixture->GetBody();
}

Entity* BodyPart::getEntity()
{
    assert(getParent()); /// FIXME this needs to be less stupid
    GameObjectBase* parent = getParent();
    while(!dynamic_cast<Entity*>(parent))
    {
        if (!parent)
            return nullptr;
        parent = parent->getParent();
    }
    return parent;
    return static_cast<Entity*>(getParent());
}
void BodyPart::setFixture(b2Fixture* _fixture)
{
    assert(!fixture);
    fixture = _fixture;
}
const Vec2f& BodyPart::getPosition()
{
    //assert(fixture);
    if (!fixture)
    {
        return {0,0};
    }
    return fixture->GetBody()->GetPosition();
}
float BodyPart::getAngle()
{
    return fixture->GetBody()->GetAngle();
}
void BodyPart::applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)
{
    fixture->GetBody()->ApplyLinearImpulse(_impulse, _point);
}
