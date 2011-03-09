#include "ProjectileDef.h"

void ProjectileDef::set(const char* _materialName, float _radius, const Vec2f position, const Vec2f velocity)
{
    setMaterial(_materialName);
    radius = _radius;
    setPosition(position);
    setVelocity(velocity);
}

void ProjectileDef::setVelocity(const Vec2f velocity)
{
    xVelocity = velocity.x;
    yVelocity = velocity.y;
}

const Vec2f ProjectileDef::getVelocity()
{
    return Vec2f(xVelocity,yVelocity);
}
