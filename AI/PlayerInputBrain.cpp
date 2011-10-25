#include "PlayerInputBrain.h"
#include <Entities/AIEntity.h>
#include <Game.h>
#include <GameModes/PlayMode.h>
#include <AI/Pathfinding/PathFollower.h>
#include <Networking/Client/NetworkedPlayerControl.h>
#include <AI/CharacterController.h>
#include <AI/AIManager.h>
PlayerInputBrain::PlayerInputBrain(unsigned short _entityKey, std::vector<std::string> controls)
{
    //ctor
    follower = nullptr;
    networkControl = nullptr;
    /*networkControl = new NetworkedPlayerControl(nullptr, _entityKey);
    networkControl->registerEvent(eUp);
    networkControl->registerEvent(eLeft);
    networkControl->registerEvent(eDown);
    networkControl->registerEvent(eRight);*/

    for (unsigned int i = 0; i < controls.size(); i++)
    {
        unsigned int control = g_InputManager.registerButtonListener(controls[i], this, this);
        buttonActionMap[control] = i;
    }
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
    //networkControl->activate();
    /*g_InputManager.registerEvent(this,eUp);
    g_InputManager.registerEvent(this,eLeft);
    g_InputManager.registerEvent(this,eDown);
    g_InputManager.registerEvent(this,eRight);*/
    g_InputManager.setActiveEvent(this);
}
void PlayerInputBrain::update()
{
    g_AIManager.setPlayerNode(mEntity->getPosition());
}
bool PlayerInputBrain::trigger(ButtonPressEvent* _event)
{
    unsigned char action = buttonActionMap.find(_event->getButton())->second;
    mEntity->getMoveControls()->booleanControls(action, true);
    return true;
}
bool PlayerInputBrain::trigger(ButtonReleaseEvent* _event)
{
    unsigned char action = buttonActionMap.find(_event->getButton())->second;
    mEntity->getMoveControls()->booleanControls(action, false);
    return true;
}
void PlayerInputBrain::buttonDown(Vec2i mouse, unsigned char button)
{
    Vec2f position = mouse.ScreenToWorldSpace();
    mEntity->weaponBegin(position);
}
void PlayerInputBrain::mouseMove(Vec2i mouse)
{
    Vec2f position = mouse.ScreenToWorldSpace();
    mEntity->weaponMove(position);
}
void PlayerInputBrain::buttonUp(Vec2i mouse, unsigned char button)
{
    Vec2f position = mouse.ScreenToWorldSpace();
    mEntity->weaponEnd(position);
}




