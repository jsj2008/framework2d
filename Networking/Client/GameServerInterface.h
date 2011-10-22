#ifndef GAMESERVERINTERFACE_H
#define GAMESERVERINTERFACE_H

#include <Input/EventListener.h>
class NetworkedPlayerControl;

class GameServerInterface : public EventListener
{
    public:
        static GameServerInterface* singleton(); /// Not permanent
        virtual bool update()=0;
        virtual void registerPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)=0;
        virtual void unregisterPlayer(NetworkedPlayerControl* _control, unsigned short _entityKey)=0;
        void activate();
    protected:
        GameServerInterface();
        virtual ~GameServerInterface();
    private:
};

#endif // GAMESERVERINTERFACE_H
