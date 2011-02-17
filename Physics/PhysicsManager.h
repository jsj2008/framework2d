#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
#define JUMPING
//#define JUMPING_SENSOR

#define WORLD_GRAVITY 1.0f
struct PhysicsFactoryDef
{
    PhysicsFactoryDef();
    b2BodyDef bodyDef;
    b2PolygonShape shape;
#ifdef JUMPING_SENSOR
    b2FixtureDef additionalFixture;
    bool useAdditionalFixture;
#endif
    float density;
};
class PhysicsManager
{
    public:
        PhysicsManager();
        void init();
        virtual ~PhysicsManager();
        b2Body* bodyFactory(PhysicsFactoryDef& def, b2Vec2& initialPosition, void* userData);
        bool update();
    protected:
    private:
        b2World* mWorld;
        unsigned int startTime;
        unsigned int stepsTaken;
};

#endif // PHYSICSMANAGER_H
