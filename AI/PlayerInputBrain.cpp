#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <AI/Pathfinding/PathFollower.h>
#include <AI/AIManager.h>
PlayerInputBrain::PlayerInputBrain()
:EventListener()
{
    //ctor
    follower = NULL;
}

PlayerInputBrain::~PlayerInputBrain()
{
    //dtor
}

void PlayerInputBrain::activate()
{
    g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);
}
void PlayerInputBrain::update()
{
    g_AIManager.setPlayerNode(mEntity->mBody);
}
void PlayerInputBrain::resetInput()
{
    mEntity->stopWalking();
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
