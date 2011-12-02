#include "CollisionObject.h"
#include <Box2D/Box2D.h>
#include <Entities/CollisionDatabase.h>

CollisionObject::CollisionObject(b2Fixture* _me, b2Fixture* _other)
{
    //ctor
    me = _me;
    other = _other;
}

CollisionObject::~CollisionObject()
{
    //dtor
}

unsigned short CollisionObject::getCollisionCategory()
{
    CollisionResponse* response = other->GetFilterData().response;
    return response->getId();
}
