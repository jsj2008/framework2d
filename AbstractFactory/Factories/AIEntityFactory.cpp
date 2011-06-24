#include "AIEntityFactory.h"
#include <Entities/AIEntity.h>
#include <AI/ZombieBrain.h>
#include <AI/PlayerInputBrain.h>
#include <Physics/PhysicsManager.h>
#include <Graphics/Skins/StaticSkin.h>
#include <Graphics/GraphicsManager.h>
#include <SharedContent/ContentManager.h>
#include <Entities/Weapons/Weapon.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <iostream>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/FactoryLoader.h>

AIEntityFactory::AIEntityFactory(FactoryLoader* loader)
{
    //ctor
    weapon = loader->get<std::string>("weapon","pistol");
    materialName = loader->get<std::string>("materialName","player");
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}

Entity* AIEntityFactory::useFactory(FactoryParameters* parameters)
{
    Brain* brain = AbstractFactories::useFactory<Brain>("PlayerInputBrainFactory", parameters);
    AIEntity* entity = new AIEntity(brain, new Weapon(g_ContentManager.getContent<WeaponContent>(weapon)));

    parameters->add<void*>("userData",entity);

    entity->mBody = AbstractFactories::useFactory<b2Body>("CharacterBodyFactory",parameters);
    entity->setWheel((b2RevoluteJoint*)parameters->get<void*>("joint",NULL));

    entity->mSkin = AbstractFactories::useFactory<Skin>("StaticSkinFactory",parameters);

    //if (aiType == ePlayerInputBrainType) FIXME
    {
        ((PlayMode*)g_Game.getGameMode(ePlayGameMode))->setBody(entity->mBody,(PlayerInputBrain*)brain);
    }
    return entity;
}
