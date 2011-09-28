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

#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/FactoryLoader.h>

AIEntityFactory::AIEntityFactory()
{

}
void AIEntityFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    weapon = loader->get<std::string>("weapon","pistol");

    bodyFactory = loader->getFactory<b2Body>("body" ,"CharacterBodyFactory");
    skinFactory = loader->getFactory<Skin>("material", "StaticSkinFactory");
    brainFactory = loader->getFactory<Brain>("brain", "PlayerInputBrainFactory");
    controllerFactory = loader->getFactory<CharacterController>("characterController", "WheelControllerFactory");
    damageSprayFactory = loader->getFactory<Entity>("damageSpray","ParticleFactory");
}

AIEntityFactory::~AIEntityFactory()
{
    //dtor
}
#include <AI/CharacterController.h>

Entity* AIEntityFactory::useFactory(FactoryParameters* parameters)
{
    //damageSprayFactory = AbstractFactories::global().getFactory<Entity>("ParticleFactory");
    Brain* brain = brainFactory->use(parameters);
    AIEntity* entity = new AIEntity(brain,
        new Weapon(g_ContentManager.getContent<WeaponContent>(weapon)),damageSprayFactory,skinFactory->use(parameters));

    parameters->add<void*>("userData",entity);

    entity->setBody(bodyFactory->use(parameters));
    CharacterController* controller = controllerFactory->use(parameters);
    entity->setController(controller);
    //entity->setWheel((b2RevoluteJoint*)parameters->get<void*>("joint",nullptr));

    return entity;
}
