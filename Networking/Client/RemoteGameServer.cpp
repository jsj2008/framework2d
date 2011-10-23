#include "RemoteGameServer.h"
#include <AbstractFactory/AbstractFactories.h>
#include <Networking/Client/NetworkedPlayerControl.h>
#include <Log/Log.h>
RemoteGameServer::RemoteGameServer()
:client("localhost", 8000)
{
    //ctor
    SingletonEventHandler<ServerMessageEvent<ClientInitialisationMessage>>::singleton().registerListener(this, {eBlockQueue | eClearQueue});
    SingletonEventHandler<ServerMessageEvent<FrameUpdateMessage>>::singleton().registerListener(this, {eBlockQueue | eClearQueue});
    frameUpdated = false;
    thisClientEntityKey = 0;
}
bool RemoteGameServer::frameUpdated;
RemoteGameServer::~RemoteGameServer()
{
    //dtor
    SingletonEventHandler<ServerMessageEvent<ClientInitialisationMessage>>::singleton().unregisterListener(this, true);
    SingletonEventHandler<ServerMessageEvent<FrameUpdateMessage>>::singleton().unregisterListener(this, true);
}

bool RemoteGameServer::update()
{
    client.update(sendingUpdate);
    sendingUpdate.clear();
    if (frameUpdated)
    {
        frameUpdated = false;
        /// Apply the received update and delete it
        for (unsigned short i = 0; i != receievedUpdate.getActionsSize(); i++)
        {
            FrameUpdate::Action action = receievedUpdate.getAction(i);
            playerControls[action.entityKey]->actionFromServer(action.action, action.pressed);
        }
        receievedUpdate.clear();
        return true;
    }
    return false;
}

void RemoteGameServer::registerPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)
{
    if (playerControls.size() <= _entityKey)
    {
        playerControls.resize(_entityKey +1);
    }
    assert(playerControls[_entityKey] == nullptr);
    playerControls[_entityKey] = _control;
    if (thisClientEntityKey == 0)
    {
        thisClientEntityKey = _entityKey;
    }
}
void RemoteGameServer::unregisterPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)
{
    assert(playerControls[_entityKey] == _control);
    playerControls[_entityKey] = nullptr;
}

void RemoteGameServer::trigger(InputActions action, bool _pressed)
{
    if (thisClientEntityKey != 0)
        sendingUpdate.addAction({thisClientEntityKey, action, _pressed});
}

bool RemoteGameServer::trigger(ServerMessageEvent<ClientInitialisationMessage>* event)
{
    FactoryParameters params;
    params.add<std::string>("name", "player");
    params.add<unsigned short>("entityKey", event->getMessage()->getEntityKey());
    /// Need to set PlayMode's camera
    AbstractFactories::global().useFactory<Camera>("BodyCameraFactory",&params);
    return true;
}
bool RemoteGameServer::trigger(ServerMessageEvent<FrameUpdateMessage>* event)
{
    frameUpdated = true;
    receievedUpdate.append(event->getMessage()->getUpdate());
    return true;
}
