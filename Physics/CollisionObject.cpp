#include "CollisionObject.h"
#include <Box2D/Box2D.h>
#include <Entities/CollisionResponse.h>

CollisionObject::CollisionObject(BodyPart* _me, BodyPart* _other)
{
    //ctor
    me = _me;
    other = _other;
}

CollisionObject::~CollisionObject()
{
    //dtor
}

