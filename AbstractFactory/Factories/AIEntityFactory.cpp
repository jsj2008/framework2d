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

AIEntityFactory::AIEntityFactory()
{

}
void AIEntityFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    weapon = loader->get<std::string>("weapon","pistol");
    materialName = loader->get<std::string>("materialName","player");
    bodyFactory = factories->getFactory<b2Body>("CharacterBodyFactory");
    skinFactory = factories->getFactory<Skin>("StaticSkinFactory");
    brainFactory = factories->getFactory<Brain>("PlayerInputBrainFactory");
    //damageSprayFactory = factories->getFactory<Entity>(loader->get<std::string>("damageSpray","spark"));
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}

Entity* AIEntityFactory::useFactory(FactoryParameters* parameters)
{
    damageSprayFactory = AbstractFactories::global().getFactory<Entity>("spark");
    Brain* brain = brainFactory->use(parameters);
    AIEntity* entity = new AIEntity(brain, new Weapon(g_ContentManager.getContent<WeaponContent>(weapon)),damageSprayFactory,skinFactory->use(parameters));

    parameters->add<void*>("userData",entity);

    entity->setBody(bodyFactory->use(parameters));
    entity->setWheel((b2RevoluteJoint*)parameters->get<void*>("joint",nullptr));

    return entity;
}
