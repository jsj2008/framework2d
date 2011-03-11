#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <AI/Pathfinding/PathFollower.h>
#include <Box2D/Box2D.h>
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
    if (follower == NULL)
    {
        follower = new PathFollower();
    }
    PathFollower::Operation operation = follower->update(mEntity->mBody->GetPosition());
    if (operation == PathFollower::Operation::eWalkLeft)
    {
        mEntity->walkLeft();
    }
    else
    {
        mEntity->walkRight();
    }
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
