#ifndef COLLISIONDATABASE_H
#define COLLISIONDATABASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <GameObject.h>
class CollisionResponse;
class b2Fixture;
class CollisionDatabase;

class CollisionDatabaseHandle
{
    public:
        CollisionDatabaseHandle(CollisionDatabase* _database, unsigned short _id);
        ~CollisionDatabaseHandle();
        void addFilter(const std::string& _collisionName);
        void addEvent(const std::string& _collisionName, const std::string& _actionName);
        void setDefaultEvent(const std::string& _actionName);
        CollisionResponse* buildResponse();
        unsigned short getId(){return id;}
        void collide(unsigned short _otherCategory, b2Fixture* _thisFixture, b2Fixture* _otherFixture);
    private:
        CollisionDatabase* database;
        unsigned short id;
        unsigned short collisionCategory;
        unsigned short collisionMask;
        std::vector<GameObjectBase::ActionHandle*> objectReaction;
        GameObjectBase::ActionHandle* defaultReaction;
};

class CollisionDatabase
{
    public:
        CollisionDatabase();
        virtual ~CollisionDatabase();
        CollisionDatabaseHandle* getHandle(const std::string& _collisionName);
    protected:
    private:
        friend class CollisionDatabaseHandle;
        std::unordered_map<std::string, CollisionDatabaseHandle*> database;
};

#endif // COLLISIONDATABASE_H
