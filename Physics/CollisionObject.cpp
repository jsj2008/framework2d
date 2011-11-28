#include "CollisionObject.h"
#include <Box2D/Box2D.h>
#include <Entities/CollisionResponse.h>

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
    CollisionResponse* response = static_cast<CollisionResponse*>(other->GetUserData());
    return response->getCategory();
}
