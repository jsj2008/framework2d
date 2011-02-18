#include "AIManager.h"
#include "AllBrains.h"
#include <Game.h>
#include <GameModes/GameMode.h>

AIManager::AIManager()
{
    //ctor
}

AIManager::~AIManager()
{
    //dtor
}

Brain* AIManager::brainFactory(BrainFactoryDef& def)
{
    Brain* brain;
    switch (def.brainType)
    {
        case ePlayerInputBrainType:
        {
            GameMode* gameMode = g_Game.getGameMode(ePlayGameMode);
            brain = new PlayerInputBrain(gameMode->mInputState);
            break;
        };
        case eBrainTypesMax:
        {
            throw "Invalid enum";
            break;
        };
    }
    return brain;
}
