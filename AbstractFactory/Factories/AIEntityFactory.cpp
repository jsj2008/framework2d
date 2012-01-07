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
#include <Physics/BodyParts/BodyPart.h>

#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/FactoryLoader.h>

AIEntityFactory::AIEntityFactory()
{

}
void AIEntityFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    //ctor
    weaponFactory = loader->getFactory<Weapon>("weapon","WeaponFactory");

    bodyFactory = loader->getFactory<BodyPart>("body" ,"CharacterBodyFactory");
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

Entity* AIEntityFactory::useFactory(FactoryParameters* _parameters)
{
    //damageSprayFactory = AbstractFactories::global().getFactory<Entity>("ParticleFactory");
    AIEntity* entity = new AIEntity;
    entity->init(brainFactory->use(_parameters, entity), weaponFactory->use(_parameters, entity) ,damageSprayFactory,skinFactory->use(_parameters, entity));

    _parameters->add<void*>("userData",entity);

    entity->setRootBody(bodyFactory->use(_parameters, entity));
    CharacterController* controller = controllerFactory->use(_parameters, entity);
    entity->setController(controller);
    //entity->setWheel((b2RevoluteJoint*)_parameters->get<void*>("joint",nullptr));

    return entity;
}
