#include "EntityFactory.h"
#include <Entities/AllEntities.h>
#include <Graphics/Camera/PhysicsCamera.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
#include <Types/Mat3x3f.h>
#include <cstring>
#define PLAYER_STARTING_HEALTH 100
#define M_PI 3.14159265358979323846
PlatformDef::PlatformDef()
{
    texture = 0;
    numPoints = 0;
}
void PlatformDef::addPoint(const Vec2f& p)
{
    assert(numPoints != b2_maxPolygonVertices);
    points[numPoints] = p;
    numPoints++;
}
#include <iostream>
using namespace std;
bool PlatformDef::sort()
{
    bool alreadySorted = false;
    for (unsigned char i = 0; i < numPoints; i++)
    {
#define points(i) points[i%numPoints]
        Vec2f start = points(i);
        Vec2f middle = points((i+1));
        Vec2f end = points((i+2));
#undef points
        Vec2f a = start - middle;
        Vec2f b = end - middle;
        a.Normalize();
        b.Normalize();

		float myAngle = atan2(a.y,a.x);
		float tAngle = atan2(b.y,b.x);
		float angle = myAngle - tAngle;
		if (angle <= -M_PI)
		{
			angle += M_PI*2.0;
		}
		if (angle >= M_PI)
		{
			angle -= M_PI*2.0;
		}
		angle *= 180/M_PI;
        if (angle < 0.0f)
        {
            if (alreadySorted)
            {
                return false;
            }
            else
            {
                for (unsigned char ii = 0; ii < numPoints/2; ii++)
                {
                    Vec2f temp = points[ii];
                    points[ii] = points[numPoints-(ii+1)];
                    points[numPoints-(ii+1)] = temp;
                }
                alreadySorted = true;
                i = 0;
            }
        }
    }
    return true;
}
EntityFactoryDef::EntityFactoryDef(EntityType _type)
:entityDef(_type),graphicsDef(eStaticSkinType)
{
}
EntityFactoryDef::EntityDef::EntityDef(EntityType _type)
{
    type = _type;
    switch (type)
    {
        case eCrateEntityType:
        {
            break;
        }
        case eStaticGeometryEntityType:
        {
            break;
        }
        case eAIEntityType:
        {
            aiEntityTypeDef.startingHealth = PLAYER_STARTING_HEALTH;
            break;
        }
        case eEntityTypeMax:
        {
            throw "Invalid enum";
        }
    }
}
EntityFactory g_EntityFactory;
void EntityFactory::init()
{
    //ctor
}

EntityFactory::~EntityFactory()
{
    //dtor
}
Entity* EntityFactory::createEntity(unsigned int index, Vec2f& initialPosition)
{
    return entityFactory(factoryDefs[index],initialPosition);
}
Entity* EntityFactory::createEntity(PlatformDef& def, Vec2f& initialPosition)
{
    unsigned int entity = addEntityDef(def);
    Entity* ret = createEntity(entity,initialPosition);
    pop();
    return ret;
}
unsigned int EntityFactory::addEntityDef(CreatureDef& def)
{
    unsigned int ret = factoryDefs.size();

    EntityFactoryDef entity(eAIEntityType);

    entity.physicsDef.bodyDef.type = b2_dynamicBody;
    //entity.physicsDef.bodyDef.fixedRotation = true;
    entity.physicsDef.shape.SetAsBox(def.dimensions.x*0.5f,def.dimensions.y*0.5f);
#ifdef JUMPING_SENSOR
    /// Sensor
    b2PolygonShape* sensorBox = new b2PolygonShape();
    sensorBox->SetAsBox(def.dimensions.x*0.5f,def.dimensions.y*0.5f);
    entity.physicsDef.additionalFixture.shape = sensorBox;
    entity.physicsDef.additionalFixture.isSensor = true;
    entity.physicsDef.useAdditionalFixture = true;
#endif

    entity.graphicsDef.graphicsDef.staticSkinDef.width = def.dimensions.x;
    entity.graphicsDef.graphicsDef.staticSkinDef.height = def.dimensions.y;
    entity.graphicsDef.graphicsDef.staticSkinDef.texture = def.texture;
    factoryDefs.push_back(entity);
    return ret;
}
unsigned int EntityFactory::addEntityDef(PlatformDef& def)
{
    unsigned int ret = factoryDefs.size();

    EntityFactoryDef entity(eStaticGeometryEntityType);

    entity.physicsDef.shape.Set(def.points,def.numPoints);

    entity.graphicsDef.type = eConvexPolygonSkinType;
    entity.graphicsDef.graphicsDef.convexPolygonSkinDef.texture = def.texture;
    entity.graphicsDef.graphicsDef.convexPolygonSkinDef.numPoints = def.numPoints;
    memcpy(entity.graphicsDef.graphicsDef.convexPolygonSkinDef.points,def.points,sizeof(Vec2f)*def.numPoints);

    factoryDefs.push_back(entity);
    return ret;
}
Entity* EntityFactory::crateEntity(CrateTypeDef& def)
{
    return new Crate;
}
Entity* EntityFactory::staticGeometryEntity(StaticGeometryTypeDef& def)
{
    return new Crate;
}
Entity* EntityFactory::aiEntity(AIEntityTypeDef& def)
{
    return new AIEntity(pAIManager->brainFactory(def.brainFactoryDef));
}
Entity* EntityFactory::createContainer(EntityFactoryDef::EntityDef& def)
{
    switch (def.type)
    {
        case eCrateEntityType:
        {
            return crateEntity(def.crateTypeDef);
        }
        case eStaticGeometryEntityType:
        {
            return staticGeometryEntity(def.staticGeometryTypeDef);
        }
        case eAIEntityType:
        {
            return aiEntity(def.aiEntityTypeDef);
        }
        case eEntityTypeMax:
        {
            break;
        }
    }
    throw "Invalid enum";
}
Entity* EntityFactory::entityFactory(EntityFactoryDef& def, Vec2f& initialPosition)
{
    Entity* entity = createContainer(def.entityDef);
    entity->mBody = g_PhysicsManager.bodyFactory(def.physicsDef,initialPosition,(void*)entity);
    entity->mSkin = g_GraphicsManager.skinFactory(def.graphicsDef);
    return entity;
}

/*void EntityFactory::setCameraTarget(const Entity* entity)
{
    static Camera* camera = NULL;
    if (camera != NULL)
    {
        delete camera;
    }
    camera = new PhysicsCamera(entity->mBody);
    g_GraphicsManager.setCamera(camera);
}*/
