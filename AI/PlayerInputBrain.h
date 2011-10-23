#ifndef PLAYERINPUTBRAIN_H
#define PLAYERINPUTBRAIN_H

#include "Brain.h"
#include <Input/EventListener.h>
class PathFollower;
class NetworkedPlayerControl;

class PlayerInputBrain : public Brain, public EventListener
{
    public:
        PlayerInputBrain(unsigned short _entityKey);
        virtual ~PlayerInputBrain();
        void trigger(InputActions actions, bool _pressed);
        void activate();
        void update();
    protected:
    private:
        PathFollower* follower;
        NetworkedPlayerControl* networkControl;
};

#endif // PLAYERINPUTBRAIN_H
