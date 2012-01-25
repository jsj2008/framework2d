#include "CollisionResponse.h"
#include <Entities/CollisionDatabase.h>

CollisionResponse::CollisionResponse(CollisionDatabaseHandle* _handle)
{
    //ctor
    handle = _handle;
}

CollisionResponse::~CollisionResponse()
{
    //dtor
}

void CollisionResponse::registerActions(GameObjectType* _type)
{

}

void CollisionResponse::addFilter(const std::string& _collisionName)
{
    handle->addFilter(_collisionName);
}
void CollisionResponse::addEvent(const std::string& _collisionName, const std::string& _actionName)
{
    handle->addEvent(_collisionName, _actionName);
}
void CollisionResponse::setDefaultEvent(const std::string& _actionName)
{
    handle->setDefaultEvent(_actionName);
}
unsigned short CollisionResponse::getId()
{
    return handle->getId();
}
