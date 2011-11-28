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

void CollisionResponse::collide(CollisionObject* _object)
{
    databaseHandle->collide(_object);
}

unsigned short CollisionResponse::getCategory()
{
    return databaseHandle->getId();
}

void CollisionResponse::registerActions()
{

}
