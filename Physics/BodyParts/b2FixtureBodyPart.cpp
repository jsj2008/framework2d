#include "b2FixtureBodyPart.h"
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>

b2FixtureBodyPart::b2FixtureBodyPart(b2Fixture* _fixture)
{
    //ctor
    fixture = _fixture;
    fixture->setBodyPart(this);
}

b2FixtureBodyPart::~b2FixtureBodyPart()
{
    //dtor
    fixture->GetBody()->DestroyFixture(fixture);
}

b2Body* b2FixtureBodyPart::getBody()
{
    return fixture->GetBody();
}

Entity* b2FixtureBodyPart::getEntity()
{
    assert(getParent()); /// FIXME this needs to be less stupid
    GameObjectBase* parent = getParent();
    while(!dynamic_cast<Entity*>(parent))
    {
        if (!parent)
            return nullptr;
        parent = parent->getParent();
    }
    return static_cast<Entity*>(parent);
}

const Vec2f& b2FixtureBodyPart::getPosition()
{
    //assert(fixture);
    if (!fixture)
    {
        return {0,0};
    }
    return fixture->GetBody()->GetPosition();
}
float b2FixtureBodyPart::getAngle()
{
    return fixture->GetBody()->GetAngle();
}
void b2FixtureBodyPart::applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)
{
    fixture->GetBody()->ApplyLinearImpulse(_impulse, _point);
}
float b2FixtureBodyPart::getArea()
{
    return fixture->GetShape()->getArea();
}
float b2FixtureBodyPart::getAreaBelowLine(float _height)
{
    return fixture->GetShape()->getAreaBelowLine(fixture, _height);
}

void b2FixtureBodyPart::applyLinearImpulse(const Vec2f& _impulse)
{
    b2MassData mass;
    fixture->GetBody()->GetMassData(&mass);
    fixture->GetBody()->ApplyLinearImpulse(_impulse, fixture->GetBody()->GetWorldPoint(mass.center));
}

float b2FixtureBodyPart::getDensity()
{
    return fixture->GetDensity();
}

Vec2f b2FixtureBodyPart::getLinearVelocity()
{
    return fixture->GetBody()->GetLinearVelocity();
}


