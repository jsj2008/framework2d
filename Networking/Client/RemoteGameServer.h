#ifndef REMOTEGAMESERVER_H
#define REMOTEGAMESERVER_H

#include <Networking/Client/GameServerInterface.h>
#include <Networking/Client/Client.h>
#include <Events/SingletonEvents/SingletonEventListener.h>
#include <Networking/Client/ServerMessageEvent.h>
#include <Networking/ClientToServer/ClientInitialisationMessage.h>
#include <Networking/ServerToClient/FrameUpdateMessage.h>
#include <Networking/FrameUpdate.h>

class RemoteGameServer : public GameServerInterface, public SingletonEventListener<ServerMessageEvent<ClientInitialisationMessage>>,
    public SingletonEventListener<ServerMessageEvent<FrameUpdateMessage>>
{
    public:
        RemoteGameServer();
        virtual ~RemoteGameServer();
        bool update();
        void registerPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey);
        void unregisterPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey);
        void trigger(InputActions action, bool _pressed);
        bool trigger(ServerMessageEvent<ClientInitialisationMessage>* event);
        bool trigger(ServerMessageEvent<FrameUpdateMessage>* event);
    protected:
    private:
        std::vector<NetworkedPlayerControl*> playerControls;
        unsigned short thisClientEntityKey;
        Client client;
        FrameUpdate receievedUpdate;
        static bool frameUpdated;
        FrameUpdate sendingUpdate;
};

#endif // REMOTEGAMESERVER_H
