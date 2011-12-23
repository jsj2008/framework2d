#include "Body.h"
#include <Box2D/Box2D.h>
#include <Physics/PhysicsManager.h>
#include <Physics/SingleFixtureBodyPart.h>
/*
Body::Body(BodyPart* _root)
{
    //ctor
    body = static_cast<SingleFixtureBodyPart*>(_root)->getBody();
    root = _root;
}

Body::~Body()
{
    //dtor
    PhysicsManager* physics = static_cast<PhysicsManager*>(body->GetWorld()->GetUserData());
    physics->destroyBody(body);
}

const Vec2f& Body::getPosition()
{
    return body->GetPosition();
}
void Body::applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)
{
    body->ApplyLinearImpulse(_impulse, _point);
}
void Body::createFixture(const b2FixtureDef* _def)
{
    body->CreateFixture(_def);
}
void Body::createFixture(const b2Shape* _def, float _density)
{
    body->CreateFixture(_def, _density);
}
float Body::getAngle()
{
    return body->GetAngle();
}

void Body::registerActions()
{

}
*/
