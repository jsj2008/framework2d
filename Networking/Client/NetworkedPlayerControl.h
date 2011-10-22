#ifndef NETWORKEDPLAYERCONTROL_H
#define NETWORKEDPLAYERCONTROL_H

#include <Input/EventListener.h>

class NetworkedPlayerControl
{
    public:
        NetworkedPlayerControl(EventListener* _listener, unsigned short _entityKey);
        virtual ~NetworkedPlayerControl();
        void actionFromServer(InputActions actions);
        void registerEvent(InputActions _action);
        void activate();
    protected:
    private:
        EventListener* listener;
        std::vector<InputActions> actions;
        unsigned short entityKey;
};

#endif // NETWORKEDPLAYERCONTROL_H
