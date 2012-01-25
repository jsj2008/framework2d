#ifndef COLLISIONRESPONSE_H
#define COLLISIONRESPONSE_H

#include <GameObject.h>
class CollisionDatabaseHandle;

class CollisionResponse : public GameObject<CollisionResponse>
{
    public:
        CollisionResponse(CollisionDatabaseHandle* _handle);
        virtual ~CollisionResponse();
        void addFilter(const std::string& _collisionName);
        void addEvent(const std::string& _collisionName, const std::string& _actionName);
        void setDefaultEvent(const std::string& _actionName);
        unsigned short getId();
        static void registerActions(GameObjectType* _type);
        static std::string name()
        {
            return "CollisionResponse";
        }
    protected:
    private:
        CollisionDatabaseHandle* handle;
};

#endif // COLLISIONRESPONSE_H
