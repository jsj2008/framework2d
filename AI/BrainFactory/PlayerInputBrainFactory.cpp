#include "PlayerInputBrainFactory.h"
#include <AI/PlayerInputBrain.h>
#include <GameModes/PlayMode.h>
#include <Game.h>

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
    PlayerInputBrain* brain = new PlayerInputBrain;
    static_cast<PlayMode*>(g_Game.getGameMode(ePlayGameMode))->setPlayerBrain(brain);
    return brain;
}
