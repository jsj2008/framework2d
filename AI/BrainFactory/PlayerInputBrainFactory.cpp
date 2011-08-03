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

}

Brain* PlayerInputBrainFactory::useFactory(FactoryParameters* parameters)
{
    PlayerInputBrain* brain = new PlayerInputBrain;
    return brain;
}
