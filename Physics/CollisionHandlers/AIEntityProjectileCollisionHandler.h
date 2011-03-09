#ifndef AIENTITYPROJECTILECOLLISIONHANDLER_H
#define AIENTITYPROJECTILECOLLISIONHANDLER_H

#include <Physics/CollisionHandlers/CollisionHandler.h>


class AIEntityProjectileCollisionHandler : public CollisionHandler
{
    public:
        AIEntityProjectileCollisionHandler();
        virtual ~AIEntityProjectileCollisionHandler();
        void handle(Entity* a, Entity* b, float totalImpulse);
    protected:
    private:
};

#endif // AIENTITYPROJECTILECOLLISIONHANDLER_H
