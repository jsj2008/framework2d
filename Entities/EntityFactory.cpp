#include "EntityFactory.h"
#include <Entities/AllEntities.h>
#include <Graphics/Camera.h>
#include <Graphics/GraphicsManager.h>
#include <AI/AIManager.h>
#define PLAYER_STARTING_HEALTH 100
EntityFactoryDef::EntityFactoryDef(EntityType _type)
:entityDef(_type),graphicsDef(eStaticSkinType)
{
    type = _type;
}
EntityFactoryDef::EntityDef::EntityDef(EntityType type)
{
    switch (type)
    {
        case ePlayerEntityType:
        {
            playerTypeDef.startingHealth = PLAYER_STARTING_HEALTH;
            break;
        }
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

Entity* EntityFactory::entityFactory(EntityFactoryDef& def, b2Vec2& initialPosition)
{
    Entity* entity;
    switch (def.type)
    {
        case ePlayerEntityType:
        {
            entity = new Player;
            break;
        }
        case eCrateEntityType:
        {
            entity = new Crate;
            break;
        }
        case eStaticGeometryEntityType:
        {
            entity = new StaticGeometry;
            break;
        }
        case eAIEntityType:
        {
            entity = new AIEntity(pAIManager->brainFactory(def.entityDef.aiEntityTypeDef.brainFactoryDef));
            break;
        }
        case eEntityTypeMax:
        {
            throw "Invalid enum";
        }
    }
    entity->mBody = pPhysicsManager->bodyFactory(def.physicsDef,initialPosition,(void*)entity);
    entity->mSkin = pGraphicsManager->skinFactory(def.graphicsDef);
    return entity;
}

void EntityFactory::setCameraTarget(const Entity* entity)
{
    Camera* camera = new Camera(entity->mBody);
    pGraphicsManager->setCamera(camera);
}
