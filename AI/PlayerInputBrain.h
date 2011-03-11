#ifndef PLAYERINPUTBRAIN_H
#define PLAYERINPUTBRAIN_H

#include "Brain.h"
#include <Input/EventListener.h>
class PathFollower;

class PlayerInputBrain : public Brain, public EventListener
{
    public:
        PlayerInputBrain();
        virtual ~PlayerInputBrain();
        void trigger(InputActions actions);
        void activate();
        void update();
    protected:
    private:
        PathFollower* follower;
};

#endif // PLAYERINPUTBRAIN_H
