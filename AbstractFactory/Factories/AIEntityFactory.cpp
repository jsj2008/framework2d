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
#include <Graphics/Camera/PhysicsCamera.h>
#include <iostream>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/FactoryLoader.h>

AIEntityFactory::AIEntityFactory(FactoryLoader* loader)
{
    //ctor
    weapon = loader->get<std::string>("weapon","pistol");
    materialName = loader->get<std::string>("materialName","player");
    bodyFactory = AbstractFactories::getFactory<b2Body>("CharacterBodyFactory");
    skinFactory = AbstractFactories::getFactory<Skin>("StaticSkinFactory");
    brainFactory = AbstractFactories::getFactory<Brain>("PlayerInputBrainFactory");
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}

Entity* AIEntityFactory::useFactory(FactoryParameters* parameters)
{
    Brain* brain = brainFactory->use(parameters);
    AIEntity* entity = new AIEntity(brain, new Weapon(g_ContentManager.getContent<WeaponContent>(weapon)));

    parameters->add<void*>("userData",entity);

    entity->mBody = bodyFactory->use(parameters);
    entity->setWheel((b2RevoluteJoint*)parameters->get<void*>("joint",nullptr));

    entity->mSkin = skinFactory->use(parameters);

    return entity;
}
