#include "AIEntityFactory.h"
#include <Factory/AIEntityDef.h>
#include <Entities/AIEntity.h>
#include <AI/ZombieBrain.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <iostream>

AIEntityFactory::AIEntityFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::EnemyCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::EnemyCategory);
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}

Entity* AIEntityFactory::createEntity(FactoryDef* data)
{
    std::cout << "Creating AI entity" << std::endl;
    AIEntityDef* def = (AIEntityDef*)data;
    Brain* brain;
    switch (def->aiType)
    {
        case AIEntityDef::eZombie:
        {
            brain = new ZombieBrain;
            break;
        }
        case AIEntityDef::eAITypesSize:
        default:
        {
            std::cout << "Invalid ai entity type" << std::endl;
            throw -1;
        }
    }
    AIEntity* entity = new AIEntity(brain);

    bodyDef.position = def->getPosition();
    shapeDef.SetAsBox(def->width*0.5f,def->height*0.5f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(data->materialName));
    return entity;
}
