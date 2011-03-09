#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

class Entity;

class CollisionHandler
{
    public:
        CollisionHandler();
        virtual ~CollisionHandler();
        virtual void handle(Entity* a, Entity* b, float totalImpulse)=0;
    protected:
    private:
};

#endif // COLLISIONHANDLER_H
