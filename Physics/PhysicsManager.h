#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
struct PhysicsFactoryDef
{
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape fixtureShape;
};
class PhysicsManager
{
    public:
        PhysicsManager();
        virtual ~PhysicsManager();
        b2Body* bodyFactory(PhysicsFactoryDef& def, b2Vec2& initialPosition, void* userData);
        void update();
    protected:
    private:
        b2World* mWorld;
        unsigned int startTime;
        unsigned int stepsTaken;
};

#endif // PHYSICSMANAGER_H
