#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
#include <stack>
class RenderCallback;
class ContactListener;
class DebugDraw;
class Body;
class ContactFilter;
class CollisionDatabase;

#define BIT(x) (1 << x)
#define JUMPING
#define WORLD_GRAVITY 9.8f

class PhysicsManager
{
    public:
        PhysicsManager(CollisionDatabase* _database);
        void init(CollisionDatabase* _database);
        virtual ~PhysicsManager();
        void clear();

        Body* createBody(b2BodyDef* def);
        b2Joint* createJoint(b2JointDef* def);
        /// You create fixtures on the body
        b2MouseJoint* createJoint(b2Body* body, Vec2f& point);
        void deleteJoint(b2Joint* joint);
        void destroyBody(b2Body* _body);
        bool update();
        void render();
        b2Body* select(Vec2f& position, void* _ignore = (void*)0xBAADF00D);
        void AABBQuery(b2QueryCallback* callback, const Vec2f& point);
        void tick();
    protected:
    private:
        void updateEntities();
        b2World* mWorld;
        ContactListener* contactListener;
        ContactFilter* contactFilter;
        RenderCallback* mRenderCallback;
        DebugDraw* debugDraw;
        std::stack<b2Body*> destroyedThisFrame;
};

#endif // PHYSICSMANAGER_H
