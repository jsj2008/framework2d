#include "PlayerInputBrainFactory.h"
#include <AI/PlayerInputBrain.h>

PlayerInputBrainFactory::PlayerInputBrainFactory()
{
    //ctor
}

PlayerInputBrainFactory::~PlayerInputBrainFactory()
{
    //dtor
}

void PlayerInputBrainFactory::init(FactoryLoader* loader, AbstractFactories* factories)
{
    controls = loader->getArray<std::string>("controls", {"Left", "Right", "Up"});
}

Brain* PlayerInputBrainFactory::useFactory(FactoryParameters* parameters)
{
    unsigned short entityKey = parameters->get<unsigned short>("entityKey", 0);
    PlayerInputBrain* brain = new PlayerInputBrain(entityKey, controls);
    return brain;
}
