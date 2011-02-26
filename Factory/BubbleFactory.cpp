#include "BubbleFactory.h"
#include <Factory/BubbleDef.h>
#include <Entities/Bubble.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>

BubbleFactory::BubbleFactory()
{
    //ctor
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::BubbleCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::BubbleCategory);
}

BubbleFactory::~BubbleFactory()
{
    //dtor
}

Entity* BubbleFactory::createEntity(FactoryDef* data)
{
    BubbleDef* def = (BubbleDef*)data;
    Entity* entity = new Bubble;

    bodyDef.position = def->position;
    shapeDef.m_radius = def->radius;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new BubbleSkin();
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(def->materialName));
    return entity;
}
