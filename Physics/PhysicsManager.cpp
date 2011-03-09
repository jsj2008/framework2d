#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <Timer.h>
#include <Entities/Entity.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/RenderCallback.h>
#include <Physics/ContactListener.h>
#include <Level/LevelManager.h>
PhysicsManager g_PhysicsManager;
PhysicsManager::PhysicsManager()
{
    //ctor
    collisionMasks[PlayerCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
    collisionMasks[CrateCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
    collisionMasks[StaticGeometryCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
    collisionMasks[BubbleCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
    collisionMasks[EnemyCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
    collisionMasks[ProjectileCategory] = PlayerCategory|CrateCategory|StaticGeometryCategory|BubbleCategory|EnemyCategory|ProjectileCategory;
}
PhysicsManager::~PhysicsManager()
{
    //dtor
}
void PhysicsManager::init()
{
    mWorld = new b2World(Vec2f(0,WORLD_GRAVITY),true);
    mRenderCallback = new RenderCallback;
    contactListener = new ContactListener;
    mWorld->SetContactListener(contactListener);
    stepsTaken = 0;
    startTime = g_Timer.getTicks();
}
void PhysicsManager::clear()
{
    b2Body* body = mWorld->GetBodyList();
    while (body != NULL)
    {
        Entity* entity = (Entity*)body->GetUserData();
        delete entity;
        body = body->GetNext();
    }
    delete mWorld;
    mWorld = new b2World(Vec2f(0,WORLD_GRAVITY),true);
}
b2Body* PhysicsManager::createBody(b2BodyDef* def)
{
    return mWorld->CreateBody(def);
}
b2Joint* PhysicsManager::createJoint(b2JointDef* def)
{
    return mWorld->CreateJoint(def);
}
void PhysicsManager::destroyBody(b2Body* body)
{
    for (b2JointEdge* jointEdge = body->GetJointList(); jointEdge != NULL;)
    {
        b2Joint* joint = jointEdge->joint;
        jointEdge = jointEdge->next;
        deleteJoint(joint);
    }
    Entity* entity = (Entity*)body->GetUserData();
    delete entity;
    mWorld->DestroyBody(body);
}
b2MouseJoint* PhysicsManager::createJoint(b2Body* body, Vec2f& point)
{
    static b2Body* groundBody = NULL;
    if (groundBody == NULL)
    {
        b2BodyDef bodyDef;
        groundBody = mWorld->CreateBody(&bodyDef);
    }
    body->SetAwake(true);
    b2MouseJointDef def;
    def.bodyA = groundBody;
    def.bodyB = body;
    def.target = point;
    def.maxForce = 1000.0f * body->GetMass();
    return (b2MouseJoint*)mWorld->CreateJoint(&def);
}
void PhysicsManager::deleteJoint(b2Joint* joint)
{
    mWorld->DestroyJoint(joint);
    g_LevelManager.removeJoint(joint);
}
bool PhysicsManager::update()
{
    unsigned int currentTime = g_Timer.getTicks();
    unsigned int totalTimePassed = currentTime - startTime;
    unsigned int stepsToTake = totalTimePassed*60.0f/1000.0f;
    bool ret = false;
    while (stepsToTake > stepsTaken)
    {
        float timestep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        mWorld->Step(timestep, velocityIterations, positionIterations);
        contactListener->process();
        updateEntities();
        stepsTaken++;
        ret = true;
    }
    return ret;
}
void PhysicsManager::updateEntities()
{
    b2Body* body = mWorld->GetBodyList();
    while (body != NULL)
    {
        Entity* entity = (Entity*)body->GetUserData();
        body = body->GetNext();
        if (entity != NULL)
            entity->update();
    }
}
void PhysicsManager::render()
{
    b2AABB aabb;
    Vec2i view = g_GraphicsManager.getView();
    float x = (float)view.x / g_GraphicsManager.getPixelsPerMeter();
    float y = (float)view.y / g_GraphicsManager.getPixelsPerMeter();
    aabb.lowerBound = Vec2f(x,y);
    Vec2i resolution = g_GraphicsManager.getResolution();
    float x2 = x + ((float)resolution.x / g_GraphicsManager.getPixelsPerMeter());
    float y2 = y + ((float)resolution.y / g_GraphicsManager.getPixelsPerMeter());
    aabb.upperBound = Vec2f(x2,y2);
    mWorld->QueryAABB(mRenderCallback,aabb);

    /*aabb.lowerBound = Vec2f(g_GraphicsManager.getView().ScreenToWorldSpace());
    x2 = aabb.lowerBound.x + ((float)g_GraphicsManager.getXRes() / g_GraphicsManager.getPixelsPerMeter());
    y2 = aabb.lowerBound.y + ((float)g_GraphicsManager.getYRes() / g_GraphicsManager.getPixelsPerMeter());
    aabb.upperBound = Vec2f(x2,y2);*/
}
class PhySimpleCallback : public b2QueryCallback
{
public:
    PhySimpleCallback(Vec2f& _position)
    {
        ret = NULL;
        position = _position;
    }
    bool ReportFixture(b2Fixture* fixture)
    {
        if (fixture->TestPoint(position))
        {
            ret = fixture->GetBody();
            if (ret->GetType() != b2_dynamicBody)
            {
                return true; /// Continue the search, we prefer dynamic bodies
            }
            else return false;
        }
        else return true;
    }
    b2Body* ret;
    Vec2f position;
};
b2Body* PhysicsManager::select(Vec2f& position)
{
    b2AABB aabb;
    PhySimpleCallback callback(position);
    aabb.lowerBound = Vec2f(position.x-0.0001f,position.y-0.0001f);
    aabb.upperBound = Vec2f(position.x+0.0001f,position.y+0.0001f);
    mWorld->QueryAABB(&callback,aabb);
    return callback.ret;
}


































