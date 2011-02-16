#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Input/InputManager.h>
PlayerInputBrain::PlayerInputBrain()
:Brain()
{
    //ctor
    g_InputManager.registerEvent(this,eUp);
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
            break;
        }
        case eDown:
        {
            break;
        }
        case eRight:
        {
            break;
        }
        case eLeft:
        {
            break;
        }
        case eInputActionsMax:
        {
            throw -1;
        }
    }
}
