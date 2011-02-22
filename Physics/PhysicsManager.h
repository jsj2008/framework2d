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
class RenderCallback;
extern class PhysicsManager
{
    public:
        void init();
        virtual ~PhysicsManager();
        void clear();
        b2Body* bodyFactory(PhysicsFactoryDef& def, b2Vec2& initialPosition, void* userData);
        void destroyBody(b2Body* body);
        b2MouseJoint* createJoint(b2Body* body, b2Vec2& point);
        void deleteJoint(b2MouseJoint* joint);
        bool update();
        void render();
        b2Body* select(b2Vec2& position);
    protected:
    private:
        void updateEntities();
        b2World* mWorld;
        RenderCallback* mRenderCallback;
        unsigned int startTime;
        unsigned int stepsTaken;
}g_PhysicsManager;

#endif // PHYSICSMANAGER_H
