#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
class RenderCallback;
class ContactListener;
class DebugDraw;
class Body;

#define BIT(x) (1 << x)
#define JUMPING
#define WORLD_GRAVITY 9.8f

class PhysicsManager
{
    public:
        PhysicsManager();
        void init();
        virtual ~PhysicsManager();
        void clear();

        Body* createBody(b2BodyDef* def);
        b2Joint* createJoint(b2JointDef* def);
        /// You create fixtures on the body
        b2MouseJoint* createJoint(b2Body* body, Vec2f& point);
        void deleteJoint(b2Joint* joint);
        bool update();
        void render();
        b2Body* select(Vec2f& position, void* _ignore = (void*)0xBAADF00D);
        enum CollisionCategory
        {
            PlayerCategory = BIT(0),
            CrateCategory = BIT(1),
            StaticGeometryCategory = BIT(2),
            BubbleCategory = BIT(3),
            EnemyCategory = BIT(4),
            ProjectileCategory = BIT(5),
            CollisionCategoriesMax
        };
        unsigned short getCollisionMask(CollisionCategory category){return collisionMasks[category];}
        void AABBQuery(b2QueryCallback* callback, const Vec2f& point);
        int getNextPositiveCollisionGroup(){return usedPositiveCollisionGroups++;}
        int getNextNegativeCollisionGroup(){return usedNegativeCollisionGroups--;}
        void tick();
    protected:
    private:
        int usedPositiveCollisionGroups;
        int usedNegativeCollisionGroups;
        unsigned short collisionMasks[CollisionCategoriesMax];
        void updateEntities();
        b2World* mWorld;
        ContactListener* contactListener;
        RenderCallback* mRenderCallback;
        DebugDraw* debugDraw;
};

#endif // PHYSICSMANAGER_H
