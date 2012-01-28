#include "b2BodyBodyPart.h"
#include <Entities/Entity.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>

b2BodyBodyPart::b2BodyBodyPart(b2Body* _body)
{
    //ctor
    body = _body;
    body->setBodyPart(this);
}

b2BodyBodyPart::~b2BodyBodyPart()
{
    //dtor
    while (body->GetFixtureList())
    {
        BodyPart* bodyPart = body->GetFixtureList()->getBodyPart();
        assert(bodyPart->getParent() == this);
        delete bodyPart;
    }
    body->GetWorld()->DestroyBody(body);
}

Entity* b2BodyBodyPart::getEntity()
{
    assert(dynamic_cast<Entity*>(getParent()));
    return static_cast<Entity*>(getParent());
}
b2Body* b2BodyBodyPart::getBody()
{
    return body;
}

float b2BodyBodyPart::getArea()
{
    throw -1;
}
float b2BodyBodyPart::getAreaBelowLine(float _height)
{
    throw -1;
}

const Vec2f& b2BodyBodyPart::getPosition()
{
    return body->GetPosition();
}
float b2BodyBodyPart::getAngle()
{
    return body->GetAngle();
}
void b2BodyBodyPart::applyLinearImpulse(const Vec2f& _impulse)
{
    b2MassData mass;
    body->GetMassData(&mass);
    body->ApplyLinearImpulse(_impulse, body->GetWorldPoint(mass.center));
}
void b2BodyBodyPart::applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)
{
    body->ApplyLinearImpulse(_impulse, _point);
}
Vec2f b2BodyBodyPart::getLinearVelocity()
{
    return body->GetLinearVelocity();
}
float b2BodyBodyPart::getDensity()
{
    float density = 0;
    for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
    {
        density += fixture->GetDensity();
    }
    return density;
}
