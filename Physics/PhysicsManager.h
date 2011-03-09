#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
class RenderCallback;
class ContactListener;

#define BIT(x) (1 << x)
#define JUMPING
#define WORLD_GRAVITY 9.8f

extern class PhysicsManager
{
    public:
        PhysicsManager();
        void init();
        virtual ~PhysicsManager();
        void clear();

        b2Body* createBody(b2BodyDef* def);
        b2Joint* createJoint(b2JointDef* def);
        /// You create fixtures on the body
        void destroyBody(b2Body* body);
        b2MouseJoint* createJoint(b2Body* body, Vec2f& point);
        void deleteJoint(b2Joint* joint);
        bool update();
        void render();
        b2Body* select(Vec2f& position);
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
    protected:
    private:
        unsigned short collisionMasks[CollisionCategoriesMax];
        void updateEntities();
        b2World* mWorld;
        ContactListener* contactListener;
        RenderCallback* mRenderCallback;
        unsigned int startTime;
        unsigned int stepsTaken;
}g_PhysicsManager;

#endif // PHYSICSMANAGER_H
