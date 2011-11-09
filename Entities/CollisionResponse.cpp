#include "CollisionResponse.h"
#include <Entities/CollisionDatabase.h>
CollisionResponse::CollisionResponse(CollisionDatabaseHandle* _databaseHandle)
{
    //ctor
    databaseHandle = _databaseHandle;
}

CollisionResponse::~CollisionResponse()
{
    //dtor
}

void CollisionResponse::collide(unsigned short _otherCategory, b2Fixture* _fixture, b2Fixture* _other)
{
    databaseHandle->collide(_otherCategory, _fixture, _other);
}

unsigned short CollisionResponse::getCategory()
{
    return databaseHandle->getId();
}

void CollisionResponse::registerActions()
{

}
