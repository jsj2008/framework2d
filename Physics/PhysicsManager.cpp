#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <Timer.h>
#include <Entities/Entity.h>
#include <AbstractFactory/AbstractFactory.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Physics/RenderCallback.h>
#include <Physics/ContactListener.h>
#include <Physics/DebugDraw.h>
#include <Physics/WaterPhysicsSystem.h>
#include <Timer.h>
#include <stack>

PhysicsManager::PhysicsManager(CollisionDatabase* _database)
{
    //ctor
    init(_database);
}
PhysicsManager::~PhysicsManager()
{
    //dtor
}
void PhysicsManager::init(CollisionDatabase* _database)
{
    mWorld = new b2World(Vec2f(0,WORLD_GRAVITY));
    //mWorld->SetUserData(this);
    mRenderCallback = new RenderCallback;
    contactListener = new ContactListener(_database);
#ifdef DEBUG_DRAW
    debugDraw = new DebugDraw;
    mWorld->SetDebugDraw(debugDraw);
#endif
    mWorld->SetContactListener(contactListener);
    attachChild(new WaterPhysicsSystem);
}
void PhysicsManager::clear()
{
    b2Body* body = mWorld->GetBodyList();
    while (body != nullptr)
    {
        Entity* entity = body->getBodyPart()->getEntity();
        delete entity;
        body = body->GetNext();
    }
    delete mWorld;
    mWorld = new b2World(Vec2f(0,WORLD_GRAVITY));
}
b2Body* PhysicsManager::createBody(b2BodyDef* _bodyDef)
{
    return mWorld->CreateBody(_bodyDef);
}
b2Joint* PhysicsManager::createJoint(b2JointDef* def)
{
    //if (mWorld)
        return mWorld->CreateJoint(def);
    /*else
        return nullptr;*/
}
void PhysicsManager::registerActions(GameObjectType* _type)
{
  _type->createActionHandle("render", &PhysicsManager::render);
  _type->createActionHandle("renderWireframe", &PhysicsManager::renderWireframe);
}

using namespace std;
b2MouseJoint* PhysicsManager::createJoint(b2Body* body, Vec2f& point)
{
    static b2Body* groundBody = nullptr;
    if (groundBody == nullptr)
    {
        //AbstractFactoryBase<BodyPart>* bodyFactory;
        //groundBody = mWorld->CreateBody(&bodyDef);
        assert(false);
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
}
void PhysicsManager::tick()
{
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 6;
    mWorld->Step(timeStep, velocityIterations, positionIterations);
    while (!destroyedThisFrame.empty())
    {
        b2Body* body = destroyedThisFrame.top();
        destroyedThisFrame.pop();
        mWorld->DestroyBody(body);
    }
    contactListener->process();
    updateEntities();
    Timer::global()->tick();
}
void PhysicsManager::updateEntities()
{
    b2Body* body = mWorld->GetBodyList();
    while (body != nullptr)
    {
        Entity* entity = static_cast<Entity*>(body->getBodyPart()->getEntity());
        body = body->GetNext();
        if (entity != nullptr)
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
void PhysicsManager::renderWireframe()
{
  mWorld->DrawDebugData();
}
class PhySimpleCallback : public b2QueryCallback
{
public:
    PhySimpleCallback(Vec2f& _position, void* _ignore)
    {
        ret = nullptr;
        position = _position;
        ignore = _ignore;
    }
    bool ReportFixture(b2Fixture* fixture)
    {
        if (fixture->TestPoint(position))
        {
            if (fixture->GetBody()->getBodyPart()->getEntity() != ignore)
            {
                ret = fixture->GetBody();
                if (ret->GetType() != b2_dynamicBody)
                {
                    return true; /// Continue the search, we prefer dynamic bodies
                }
                else return false;
            }
        }
        return true;
    }
    b2Body* ret;
    Vec2f position;
    void* ignore;
};
b2Body* PhysicsManager::select(Vec2f& position, void* ignore)
{
    PhySimpleCallback callback(position, ignore);
    b2AABB aabb;
    aabb.lowerBound = Vec2f(position.x-0.0001f,position.y-0.0001f);
    aabb.upperBound = Vec2f(position.x+0.0001f,position.y+0.0001f);
    mWorld->QueryAABB(&callback,aabb);
    return callback.ret;
}
void PhysicsManager::AABBQuery(b2QueryCallback* callback, const Vec2f& point)
{
    b2AABB aabb;
    aabb.lowerBound = Vec2f(point.x-0.0001f,point.y-0.0001f);
    aabb.upperBound = Vec2f(point.x+0.0001f,point.y+0.0001f);
    mWorld->QueryAABB(callback,aabb);
}

void PhysicsManager::destroyBody(b2Body* _body)
{
    if (mWorld->IsLocked())
    {
        destroyedThisFrame.push(_body);
        for (b2Fixture* fixture = _body->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            fixture->SetFilterData({nullptr});
        }
        //_body->SetUserData(nullptr);
        assert(false); /// FIXME Need to make sure whatever this was for is clear
    }
    else
    {
        mWorld->DestroyBody(_body);
    }
}
































