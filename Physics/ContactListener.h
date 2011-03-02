#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <queue>
#include <Box2D/Box2D.h>
class Entity;

class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();
        void process();
    protected:
    private:
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        struct HighVelocityImpact
        {
            Entity* entityA;
            Entity* entityB;
        };
        std::queue<HighVelocityImpact> highVelocityImpacts;

};

#endif // CONTACTLISTENER_H
