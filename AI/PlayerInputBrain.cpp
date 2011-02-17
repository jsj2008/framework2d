#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Input/InputManager.h>
PlayerInputBrain::PlayerInputBrain()
:Brain()
{
    //ctor
    g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);
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
        case eInputActionsMax:
        {
            break;
        }
    }
    throw -1;
}
