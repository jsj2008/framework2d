#include "CrateFactory.h"
#include <Entities/Crate.h>
#include <Factory/CrateDef.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
using namespace std;

CrateFactory::CrateFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    fixtureDef.density = 10.0f;
    fixtureDef.shape = &shapeDef;
    fixtureDef.filter.categoryBits = PhysicsManager::CrateCategory;
    fixtureDef.filter.maskBits = g_PhysicsManager.getCollisionMask(PhysicsManager::CrateCategory);
}

CrateFactory::~CrateFactory()
{
    //dtor
}
Entity* CrateFactory::createEntity(FactoryDef* data)
{
    CrateDef* def = (CrateDef*)data;
    Entity* entity = new Crate;

    bodyDef.position = def->position;
    bodyDef.angle = data->rotation;
    shapeDef.SetAsBox(def->width*0.5f,def->height*0.5f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial(def->materialName));
    return entity;
}
