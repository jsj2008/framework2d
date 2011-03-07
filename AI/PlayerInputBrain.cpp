#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
PlayerInputBrain::PlayerInputBrain()
:EventListener()
{
    //ctor
}

PlayerInputBrain::~PlayerInputBrain()
{
    //dtor
}

void PlayerInputBrain::trigger(InputActions action)
{
    switch (action)
    {
        case eUp:
        {
            mEntity->jump();
            return;
        }
        case eDown:
        {
            return;
        }
        case eRight:
        {
            mEntity->walkRight();
            return;
        }
        case eLeft:
        {
            mEntity->walkLeft();
            return;
        }
        case ePlus:
        case eMinus:
        case eInputActionsMax:
        {
            break;
        }
    }
    throw -1;
}
