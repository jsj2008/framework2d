#ifndef STATICGEOMETRYAIENTITYCOLLISIONHANDLER_H
#define STATICGEOMETRYAIENTITYCOLLISIONHANDLER_H

#include <Physics/CollisionHandlers/CollisionHandler.h>

class StaticGeometryAIEntityCollisionHandler : public CollisionHandler
{
    public:
        StaticGeometryAIEntityCollisionHandler();
        virtual ~StaticGeometryAIEntityCollisionHandler();
        void handle(Entity* a, Entity* b, float totalImpulse);
    protected:
    private:
};

#endif // STATICGEOMETRYAIENTITYCOLLISIONHANDLER_H
