#include "CollisionDatabase.h"
#include <Entities/CollisionResponse.h>
#include <Box2D/Box2D.h>

CollisionDatabase::CollisionDatabase()
{
    //ctor
}

CollisionDatabase::~CollisionDatabase()
{
    //dtor
}

CollisionDatabaseHandle::CollisionDatabaseHandle(CollisionDatabase* _database, unsigned short _id)
{
    //ctor
    database = _database;
    id = _id;
    collisionCategory = 1 << id;
    collisionMask = -1;
}

void CollisionDatabaseHandle::addFilter(const std::string& _collisionName)
{
    CollisionDatabaseHandle* handle = database->getHandle(_collisionName);
    collisionMask &= !(1 << handle->getId());
}
void CollisionDatabaseHandle::addEvent(const std::string& _collisionName, const std::string& _actionName)
{
    CollisionDatabaseHandle* other = database->getHandle(_collisionName);
    GameObjectBase::ActionHandle* action = GameObjectBase::getActionHandle(_actionName);
    assert(action);
    events.push_back({other, action});
    if (objectReaction.size() <= other->getId())
    {
        objectReaction.resize(other->getId() + 1);
    }
    assert(objectReaction[other->getId()] == nullptr);
    objectReaction[other->getId()] = action;
}

CollisionResponse* CollisionDatabaseHandle::buildResponse()
{
    return new CollisionResponse(this);
}
#include <iostream>
void CollisionDatabaseHandle::collide(unsigned short _otherCategory, b2Fixture* _thisFixture, b2Fixture* _otherFixture)
{
    if (_otherCategory < objectReaction.size())
    {
        GameObjectBase::ActionHandle* action = objectReaction[_otherCategory];
        if (action != nullptr)
        {
            /// Execute
            GameObjectBase* object = static_cast<GameObjectBase*>(_thisFixture->GetBody()->GetUserData());
            action->execute(object);
            std::cout << "Action executed\n" << std::endl;
        }
        else std::cout << "Action not executed : NULL" << std::endl;
    }
    else std::cout << "Action not executed" << std::endl;
}
CollisionDatabaseHandle* CollisionDatabase::getHandle(const std::string& _collisionName)
{
    auto iter = database.find(_collisionName);
    if (iter != database.end())
    {
        return iter->second;
    }
    else
    {
        CollisionDatabaseHandle* handle = new CollisionDatabaseHandle(this, database.size());
        database[_collisionName] = handle;
        return handle;
    }
}
