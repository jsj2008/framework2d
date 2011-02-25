#include "PlayerFactory.h"
#include <Entities/AIEntity.h>
#include <Graphics/Skins/StaticSkin.h>
#include <AI/PlayerInputBrain.h>
#include <Factory/FactoryDef.h>
#include <Game.h>
#include <GameModes/GameMode.h>
#include <cstring>

PlayerFactory::PlayerFactory()
{
    //ctor
    physicsDef.bodyDef.type = b2_dynamicBody;
    physicsDef.shape.SetAsBox(2*0.5f,2*0.5f);
}

PlayerFactory::~PlayerFactory()
{
    //dtor
}

Entity* PlayerFactory::createEntity(FactoryDef* data)
{
    Entity* entity = new AIEntity(new PlayerInputBrain(g_Game.getGameMode(ePlayGameMode)->getInputState()));

    physicsDef.bodyDef.position = data->position;
    physicsDef.bodyDef.userData = (void*)entity;
    entity->mBody = g_PhysicsManager.createBody(&physicsDef.bodyDef);
    entity->mBody->CreateFixture(&physicsDef.shape, physicsDef.density);

    entity->mSkin = new StaticSkin(2,2);
    setMaterial(entity->mSkin,g_GraphicsManager.getMaterial("player"));
    return entity;
}
