#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <AI/Pathfinding/PathFollower.h>
#include <Networking/Client/NetworkedPlayerControl.h>
#include <AI/AIManager.h>
PlayerInputBrain::PlayerInputBrain(unsigned short _entityKey)
:EventListener()
{
    //ctor
    follower = nullptr;
    networkControl = new NetworkedPlayerControl(this, _entityKey);
    networkControl->registerEvent(eUp);
    networkControl->registerEvent(eLeft);
    networkControl->registerEvent(eDown);
    networkControl->registerEvent(eRight);
}

PlayerInputBrain::~PlayerInputBrain()
{
    //dtor
    delete networkControl;
    /*g_InputManager.unregisterEvent(this,eUp);
    g_InputManager.unregisterEvent(this,eLeft);
    g_InputManager.unregisterEvent(this,eDown);
    g_InputManager.unregisterEvent(this,eRight);*/
}

void PlayerInputBrain::activate()
{
    networkControl->activate();
    /*g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);*/
}
void PlayerInputBrain::update()
{
    g_AIManager.setPlayerNode(mEntity->getPosition());
}
void PlayerInputBrain::trigger(InputActions action, bool _pressed)
{
    if (_pressed)
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
            /*case eResetInput:
            {
                mEntity->stopWalking();
                return;
            }*/
            case ePlus:
            case eMinus:
            case eInputActionsMax:
            {
                break;
            }
        }
        throw -1;
    }
    else
    {
        mEntity->stopWalking();
    }
}
