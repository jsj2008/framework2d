#ifndef WILDCARDPROJECTILECOLLISIONHANDLER_H
#define WILDCARDPROJECTILECOLLISIONHANDLER_H

#include <Physics/CollisionHandlers/CollisionHandler.h>


class WildcardProjectileCollisionHandler : public CollisionHandler
{
    public:
        WildcardProjectileCollisionHandler();
        virtual ~WildcardProjectileCollisionHandler();
        void handle(Entity* a, Entity* b, float totalImpulse);
    protected:
    private:
};

#endif // WILDCARDPROJECTILECOLLISIONHANDLER_H
