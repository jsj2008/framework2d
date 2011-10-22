#include "NetworkedPlayerControl.h"
#include <Networking/Client/GameServerInterface.h>

NetworkedPlayerControl::NetworkedPlayerControl(EventListener* _listener, unsigned short _entityKey)
{
    //ctor
    listener = _listener;
    entityKey = _entityKey;
    GameServerInterface::singleton()->registerPlayer(this, entityKey);
}

NetworkedPlayerControl::~NetworkedPlayerControl()
{
    //dtor
    GameServerInterface::singleton()->unregisterPlayer(this, entityKey);
}

/*void NetworkedPlayerControl::trigger(InputActions actions)
{
    GameServerInterface::singleton()->trigger(InputActions _action)
}*/
void NetworkedPlayerControl::actionFromServer(InputActions _action)
{
    for (unsigned int i = 0; i < actions.size(); i++)
    {
        if (actions[i] == _action)
        {
            listener->trigger(_action);
            break;
        }
    }
}
void NetworkedPlayerControl::activate()
{
    /*for (unsigned int i = 0; i < actions.size(); i++)
    {
        g_InputManager.registerEvent(this, actions[i]);
    }*/
    GameServerInterface::singleton()->activate();
}

void NetworkedPlayerControl::registerEvent(InputActions _action)
{
    actions.push_back(_action);
}
