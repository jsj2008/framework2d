#include "GameServerInterface.h"
#include <Networking/Client/SinglePlayerGameServer.h>
#include <Networking/Client/RemoteGameServer.h>

GameServerInterface::GameServerInterface()
{
    //ctor
}

GameServerInterface::~GameServerInterface()
{
    //dtor
}

void GameServerInterface::activate()
{
    for (int action = 0; action < eInputActionsMax; action++)
        g_InputManager.registerEvent(this, static_cast<InputActions>(action));
}
GameServerInterface* GameServerInterface::singleton()
{
    static SinglePlayerGameServer server;
    return &server;
}
