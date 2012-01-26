#ifndef COLLISIONDATABASE_H
#define COLLISIONDATABASE_H

#include <string>
#include <vector>
#include <unordered_map>
class b2Fixture;
class CollisionDatabase;
class CollisionObject;
class ContactFactory;
class Contact;
class b2Contact;
class ActionHandle;

class CollisionDatabaseHandle
{
    public:
        CollisionDatabaseHandle(CollisionDatabase* _database, unsigned short _id);
        ~CollisionDatabaseHandle();
        void addFilter(const std::string& _collisionName);
        void addEvent(const std::string& _collisionName, const std::string& _actionName);
        void setDefaultEvent(const std::string& _actionName);
        unsigned short getId(){return id;}
        CollisionDatabase* getDatabase(){return database;}
        bool getFiltered(unsigned short _b);
    private:
        CollisionDatabase* database;
        unsigned short id;
};

class CollisionDatabase
{
    public:
        CollisionDatabase();
        virtual ~CollisionDatabase();
        CollisionDatabaseHandle* getHandle(const std::string& _collisionName);
        Contact* createContact(unsigned short _categoryA, unsigned short _categoryB);
    protected:
    private:
        std::unordered_map<std::string, CollisionDatabaseHandle*> database;
        ContactFactory*** contactFactories;

        friend class CollisionDatabaseHandle;
        void addFilter(unsigned short _a, unsigned short _b);
        void addEvent(unsigned short _a, unsigned short _b, ActionHandle* _action);
        bool getFiltered(unsigned short _a, unsigned short _b);
        void setDefaultEvent(unsigned short _a, ActionHandle* _action);
};

#endif // COLLISIONDATABASE_H
