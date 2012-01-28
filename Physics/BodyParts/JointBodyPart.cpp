#include "JointBodyPart.h"
#include <Types/Vec2f.h>

JointBodyPart::JointBodyPart(b2RevoluteJoint* _joint)
{
    //ctor
}

JointBodyPart::~JointBodyPart()
{
    //dtor
}

void JointBodyPart::setMotorSpeed(float _speed)
{

}

float JointBodyPart::getArea()
{
    throw -1;
}
float JointBodyPart::getAreaBelowLine(float _height)
{
    throw -1;
}

Entity* JointBodyPart::getEntity()
{
    throw -1;
}
const Vec2f& JointBodyPart::getPosition()
{
    throw -1;
}
float JointBodyPart::getAngle()
{
    throw -1;
}
void JointBodyPart::applyLinearImpulse(const Vec2f& _impulse)
{
    throw -1;
}
void JointBodyPart::applyLinearImpulse(const Vec2f& _impulse, const Vec2f& _point)
{
    throw -1;
}
Vec2f JointBodyPart::getLinearVelocity()
{
    throw -1;
}
float JointBodyPart::getDensity()
{
    throw -1;
}
