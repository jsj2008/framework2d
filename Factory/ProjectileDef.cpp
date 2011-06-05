#include "ProjectileDef.h"

ProjectileDef::ProjectileDef()
{

}
ProjectileDef::ProjectileDef(const char* _materialName, float _radius, const Vec2f& _position, const Vec2f& _velocity)
{
    setMaterial(_materialName);
    radius = _radius;
    position = _position;
    velocity = _velocity;
}
