#include "CollisionDatabase.h"
#include <Entities/CollisionDatabase.h>
#include <Box2D/Box2D.h>
#include <Log/Log.h>
#include <Physics/CollisionObject.h>
#include <Physics/Contact.h>
#include <Physics/ContactFactory.h>

CollisionDatabase::CollisionDatabase()
{
    //ctor
    contactFactories = nullptr;
}

CollisionDatabase::~CollisionDatabase()
{
    //dtor
}

CollisionResponse::CollisionResponse(CollisionDatabase* _database, unsigned short _id)
{
    //ctor
    database = _database;
    id = _id;
}

CollisionResponse::~CollisionResponse()
{

}

Contact* CollisionDatabase::createContact(unsigned short _categoryA, unsigned short _categoryB)
{
    bool inverted = _categoryA > _categoryB;
    ContactFactory* factory = contactFactories[_categoryA][_categoryB];
    if (factory != nullptr)
    {
        Contact* contact = factory->createContact(inverted);
        return contact;
    }
    return nullptr;
}

void CollisionResponse::addFilter(const std::string& _collisionName)
{
    CollisionResponse* handle = database->getHandle(_collisionName);
    database->addFilter(id, handle->id);
}
void CollisionResponse::addEvent(const std::string& _collisionName, const std::string& _actionName)
{
    CollisionResponse* other = database->getHandle(_collisionName);
    ActionHandle* action = GameObjectType::staticGetActionHandle(_actionName);
    assert(action);
    database->addEvent(id, other->getId(), action);
}
void CollisionResponse::setDefaultEvent(const std::string& _actionName)
{
    database->setDefaultEvent(id, GameObjectType::staticGetActionHandle(_actionName));
}

CollisionResponse* CollisionDatabase::getHandle(const std::string& _collisionName)
{
    auto iter = database.find(_collisionName);
    if (iter != database.end())
    {
        return iter->second;
    }
    else
    {
        CollisionResponse* handle = new CollisionResponse(this, database.size());
        database[_collisionName] = handle;
        unsigned short size = database.size();

        ContactFactory*** newContactFactories;
        newContactFactories = new ContactFactory**[size];
        for (unsigned int i = 0; i < size; i++)
        {
            newContactFactories[i] = new ContactFactory*[size];
        }
        for (unsigned int i = 0; i < size-1; i++)
        {
            for (unsigned int ii = 0; ii < size-1; ii++)
            {
                newContactFactories[i][ii] = contactFactories[i][ii];
            }
        }
        for (unsigned int i = 0; i < size; i++)
        {
            newContactFactories[size-1][i] = newContactFactories[i][size-1] = new ContactFactory;
        }
        for (unsigned int i = 0; i < size-1; i++)
        {
            delete[] contactFactories[i];
        }
        delete[] contactFactories;
        contactFactories = newContactFactories;

        return handle;
    }
}

void CollisionDatabase::addFilter(unsigned short _a, unsigned short _b)
{
    contactFactories[_a][_b]->filter();
    contactFactories[_b][_a]->filter();
}
void CollisionDatabase::addEvent(unsigned short _a, unsigned short _b, ActionHandle* _action)
{
    contactFactories[_a][_b]->setEvent(_action, _a < _b);
}
void CollisionDatabase::setDefaultEvent(unsigned short _a, ActionHandle* _action)
{
    for (unsigned int i = 0; i < database.size(); i++)
        contactFactories[_a][i]->setEvent(_action, _a < i);
}

void CollisionResponse::registerActions(GameObjectType* _type)
{

}










