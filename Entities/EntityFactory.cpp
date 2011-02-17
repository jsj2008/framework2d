#include "EntityFactory.h"
#include <Entities/AllEntities.h>
#include <Graphics/Camera.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
#include <cstring>
#define PLAYER_STARTING_HEALTH 100
PlatformDef::PlatformDef()
{
    texture = -1;
    numPoints = 0;
}
void PlatformDef::addPoint(const b2Vec2& p)
{
    assert(numPoints != b2_maxPolygonVertices);
    points[numPoints] = p;
    numPoints++;
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
void EntityFactory::init(PhysicsManager* _PhysicsManager)
{
    //ctor
    pPhysicsManager = _PhysicsManager;
}

EntityFactory::~EntityFactory()
{
    //dtor
}
Entity* EntityFactory::createEntity(unsigned int index, b2Vec2& initialPosition)
{
    return entityFactory(factoryDefs[index],initialPosition);
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
    memcpy(entity.graphicsDef.graphicsDef.convexPolygonSkinDef.points,def.points,sizeof(b2Vec2)*def.numPoints);

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
Entity* EntityFactory::entityFactory(EntityFactoryDef& def, b2Vec2& initialPosition)
{
    Entity* entity = createContainer(def.entityDef);
    entity->mBody = pPhysicsManager->bodyFactory(def.physicsDef,initialPosition,(void*)entity);
    entity->mSkin = g_GraphicsManager.skinFactory(def.graphicsDef);
    return entity;
}

void EntityFactory::setCameraTarget(const Entity* entity)
{
    Camera* camera = new Camera(entity->mBody);
    g_GraphicsManager.setCamera(camera);
}
