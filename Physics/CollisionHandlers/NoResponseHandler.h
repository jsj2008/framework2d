#ifndef NORESPONSEHANDLER_H
#define NORESPONSEHANDLER_H

#include <Physics/CollisionHandlers/CollisionHandler.h>


class NoResponseHandler : public CollisionHandler
{
    public:
        NoResponseHandler();
        virtual ~NoResponseHandler();
        void handle(Entity* a, Entity* b, float totalImpulse){}
    protected:
    private:
};

#endif // NORESPONSEHANDLER_H
