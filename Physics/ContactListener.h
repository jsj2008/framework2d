#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <queue>
#include <stack>
#include <Box2D/Box2D.h>
#include <Entities/Entity.h>
class Entity;
class CollisionHandler;

class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();
        void process();
    protected:
    private:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        struct HighVelocityImpact
        {
            HighVelocityImpact(Entity* a, Entity* b, float tI):entityA(a),entityB(b),totalImpulse(tI){}
            Entity* entityA;
            Entity* entityB;
            float totalImpulse;
        };
        std::queue<HighVelocityImpact> highVelocityImpacts;
        CollisionHandler* handlers[eEntityTypeMax][eEntityTypeMax];
        std::stack<std::pair<b2Fixture*, b2Fixture*>> collidedFixtures;
};

#endif // CONTACTLISTENER_H
