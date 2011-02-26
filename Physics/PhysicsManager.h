#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <Box2D/Box2D.h>
#define JUMPING

#define WORLD_GRAVITY 9.8f

class RenderCallback;
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
        void deleteJoint(b2MouseJoint* joint);
        bool update();
        void render();
        b2Body* select(Vec2f& position);
        enum CollisionCategory
        {
            PlayerCategory = 0x0001,
            CrateCategory,
            StaticGeometryCategory,
            BubbleCategory,
            CollisionCategoriesMax
        };
        unsigned short getCollisionMask(CollisionCategory category){return collisionMasks[category];}
    protected:
    private:
        unsigned short collisionMasks[CollisionCategoriesMax];
        void updateEntities();
        b2World* mWorld;
        RenderCallback* mRenderCallback;
        unsigned int startTime;
        unsigned int stepsTaken;
}g_PhysicsManager;

#endif // PHYSICSMANAGER_H
