#include "BubbleFactory.h"
#include <Factory/BubbleDef.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Graphics/Skins/BubbleSkin.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>

BubbleFactory::BubbleFactory()
{
    //ctor
    fixtureDef.isSensor = true;
    fixtureDef.shape = &shapeDef;
}

BubbleFactory::~BubbleFactory()
{
    //dtor
}

Entity* BubbleFactory::createEntity(FactoryDef* data)
{
    BubbleDef* def = (BubbleDef*)data;
    Entity* entity;
    switch (def->type)
    {
        case Bubble::eSuctionBubbleType:
        {
            entity = new SuctionBubble;
            break;
        }
        case Bubble::eUpwardsGravityBubbleType:
        {
            entity = new UpwardsGravityBubble;
            break;
        }
        case Bubble::eBubbleTypesMax:
        default:
        {
            return NULL;
        }
    }

    bodyDef.position = def->getPosition();
    shapeDef.m_radius = def->radius;
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new BubbleSkin(def->radius);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(def->materialName));
    return entity;
}
