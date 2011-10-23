#ifndef SINGLEPLAYERGAMESERVER_H
#define SINGLEPLAYERGAMESERVER_H

#include <Networking/Client/GameServerInterface.h>


class SinglePlayerGameServer : public GameServerInterface
{
    public:
        SinglePlayerGameServer();
        virtual ~SinglePlayerGameServer();
        bool update();
        void registerPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey);
        void unregisterPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey);
        void trigger(InputActions action, bool _pressed);
    protected:
    private:
        unsigned int stepsTaken, startTime;
        NetworkedPlayerControl* control;
};

#endif // SINGLEPLAYERGAMESERVER_H
