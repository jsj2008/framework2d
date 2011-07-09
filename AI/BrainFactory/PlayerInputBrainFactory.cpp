#include "PlayerInputBrainFactory.h"
#include <AI/PlayerInputBrain.h>
#include <GameModes/PlayMode.h>
#include <Game.h>

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
    static_cast<PlayMode*>(g_Game.getGameMode(ePlayGameMode))->setPlayerBrain(brain);
    return brain;
}
