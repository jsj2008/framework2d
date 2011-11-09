#ifndef COLLISIONRESPONSE_H
#define COLLISIONRESPONSE_H

#include <GameObject.h>
class b2Fixture;
class CollisionDatabaseHandle;

class CollisionResponse : public GameObject<CollisionResponse>
{
    public:
        CollisionResponse(CollisionDatabaseHandle* _databaseHandle);
        virtual ~CollisionResponse();
        void collide(unsigned short _otherCategory, b2Fixture* _fixture, b2Fixture* _other);
        unsigned short getCategory();
        static void registerActions();
        static std::string name()
        {
            return "CollisionResponse";
        }
    protected:
    private:
        CollisionDatabaseHandle* databaseHandle;
};

#endif // COLLISIONRESPONSE_H
