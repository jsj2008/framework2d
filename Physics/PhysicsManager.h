#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <GameObject.h>
#include <stack>
class RenderCallback;
class ContactListener;
class DebugDraw;
class BodyPart;
class BodyPart;
class ContactFilter;
class CollisionDatabase;
class b2World;
class b2Body;
class b2BodyDef;
class b2Joint;
class b2JointDef;
class b2MouseJoint;
class b2QueryCallback;
class Vec2f;

#define BIT(x) (1 << x)
#define JUMPING
#define WORLD_GRAVITY 9.8f

class PhysicsManager: public GameObject<PhysicsManager>
{
    public:
        PhysicsManager(CollisionDatabase* _database);
        void init(CollisionDatabase* _database);
        virtual ~PhysicsManager();
        void clear();

        b2Body* createBody(b2BodyDef* _bodyDef);
        b2Joint* createJoint(b2JointDef* def);
        /// You create fixtures on the body
        b2MouseJoint* createJoint(b2Body* body, Vec2f& point);
        void deleteJoint(b2Joint* joint);
        void destroyBody(b2Body* _body);
        bool update();
        void render();
  void renderWireframe();
        b2Body* select(Vec2f& position, void* _ignore = (void*)0xBAADF00D);
        void AABBQuery(b2QueryCallback* callback, const Vec2f& point);
        void tick();
        static std::string name()
        {
            return "PhysicsManager";
        }
        static void registerActions(GameObjectType* _type);
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
