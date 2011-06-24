#include "PlayerInputBrainFactory.h"
#include <AI/PlayerInputBrain.h>


PlayerInputBrainFactory::PlayerInputBrainFactory(FactoryLoader* _loader)
{
    //ctor
}

PlayerInputBrainFactory::~PlayerInputBrainFactory()
{
    //dtor
}

Brain* PlayerInputBrainFactory::useFactory(FactoryParameters* parameters)
{
    return new PlayerInputBrain;
}
