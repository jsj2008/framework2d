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

CollisionDatabaseHandle::CollisionDatabaseHandle(CollisionDatabase* _database, unsigned short _id)
{
    //ctor
    database = _database;
    id = _id;
}

CollisionDatabaseHandle::~CollisionDatabaseHandle()
{

}
bool CollisionDatabaseHandle::getFiltered(unsigned short _b)
{
    return database->getFiltered(getId(), _b);
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

void CollisionDatabaseHandle::addFilter(const std::string& _collisionName)
{
    CollisionDatabaseHandle* handle = database->getHandle(_collisionName);
    database->addFilter(id, handle->id);
}
void CollisionDatabaseHandle::addEvent(const std::string& _collisionName, const std::string& _actionName)
{
    CollisionDatabaseHandle* other = database->getHandle(_collisionName);
    ActionHandle* action = GameObjectType::staticGetActionHandle(_actionName);
    assert(action);
    database->addEvent(id, other->getId(), action);
}
void CollisionDatabaseHandle::setDefaultEvent(const std::string& _actionName)
{
    database->setDefaultEvent(id, GameObjectType::staticGetActionHandle(_actionName));
}

CollisionDatabaseHandle* CollisionDatabase::getHandle(const std::string& _collisionName)
{
    unsigned short oldSize = database.size();
    auto iter = database.find(_collisionName);
    CollisionDatabaseHandle* handle;
    if (iter != database.end())
    {
        handle = iter->second;
    }
    else
    {
        handle = new CollisionDatabaseHandle(this, oldSize);
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
    }
    return handle;
}

void CollisionDatabase::addFilter(unsigned short _a, unsigned short _b)
{
    contactFactories[_a][_b]->filter();
    contactFactories[_b][_a]->filter();
}
bool CollisionDatabase::getFiltered(unsigned short _a, unsigned short _b)
{
    return contactFactories[_a][_b]->getFiltered();
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













