#include "PlayerFactory.h"
#include <Entities/AIEntity.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <AI/PlayerInputBrain.h>
#include <Factory/CrateDef.h>
#include <Game.h>
#include <GameModes/GameMode.h>
#include <cstring>

PlayerFactory::PlayerFactory()
{
    //ctor
    bodyDef.type = b2_dynamicBody;
    fixtureDef.shape = &shapeDef;
}

PlayerFactory::~PlayerFactory()
{
    //dtor
}

Entity* PlayerFactory::createEntity(FactoryDef* data)
{
    CrateDef* def = (CrateDef*)data;
    Entity* entity = new AIEntity(new PlayerInputBrain(g_Game.getGameMode(ePlayGameMode)->getInputState()));

    bodyDef.position = def->getPosition();
    shapeDef.SetAsBox(def->width*0.5f,def->height*0.5f);
    bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&bodyDef);
    entity->mBody->CreateFixture(&fixtureDef);

    entity->mSkin = new StaticSkin(def->width,def->height);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial("player"));
    return entity;
}
