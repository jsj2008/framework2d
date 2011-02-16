#include "EntityFactory.h"
#include <Entities/AllEntities.h>
#include <Graphics/Camera.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
#define PLAYER_STARTING_HEALTH 100
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

EntityFactory::EntityFactory(GraphicsManager* _GraphicsManager,
                            PhysicsManager* _PhysicsManager)
{
    //ctor
    pGraphicsManager = _GraphicsManager;
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

    entity.physicsDef.shape.SetAsBox(def.dimensions.x,def.dimensions.y);
    entity.graphicsDef.graphicsDef.staticSkinDef.width = def.dimensions.x;
    entity.graphicsDef.graphicsDef.staticSkinDef.height = def.dimensions.y;
    entity.graphicsDef.graphicsDef.staticSkinDef.texture = def.texture;
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
    entity->mSkin = pGraphicsManager->skinFactory(def.graphicsDef);
    return entity;
}

void EntityFactory::setCameraTarget(const Entity* entity)
{
    Camera* camera = new Camera(entity->mBody);
    pGraphicsManager->setCamera(camera);
}
