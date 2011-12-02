#ifndef COLLISIONDATABASE_H
#define COLLISIONDATABASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <GameObject.h>
class b2Fixture;
class CollisionDatabase;
class CollisionObject;
class ContactFactory;
class Contact;
class b2Contact;

class CollisionResponse : public GameObject<CollisionResponse>
{
    public:
        CollisionResponse(CollisionDatabase* _database, unsigned short _id);
        ~CollisionResponse();
        void addFilter(const std::string& _collisionName);
        void addEvent(const std::string& _collisionName, const std::string& _actionName);
        void setDefaultEvent(const std::string& _actionName);
        unsigned short getId(){return id;}
        static void registerActions();
        static std::string name()
        {
            return "CollisionResponse";
        }
    private:
        CollisionDatabase* database;
        unsigned short id;
};

class CollisionDatabase
{
    public:
        CollisionDatabase();
        virtual ~CollisionDatabase();
        CollisionResponse* getHandle(const std::string& _collisionName);
        Contact* createContact(unsigned short _categoryA, unsigned short _categoryB);
    protected:
    private:
        std::unordered_map<std::string, CollisionResponse*> database;
        ContactFactory*** contactFactories;

        friend class CollisionResponse;
        void addFilter(unsigned short _a, unsigned short _b);
        void addEvent(unsigned short _a, unsigned short _b, GameObjectBase::ActionHandle* _action);
        void setDefaultEvent(unsigned short _a, GameObjectBase::ActionHandle* _action);
};

#endif // COLLISIONDATABASE_H
