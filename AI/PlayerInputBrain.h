#ifndef PLAYERINPUTBRAIN_H
#define PLAYERINPUTBRAIN_H

#include "Brain.h"
#include <Input/EventListener.h>
class InputState;


class PlayerInputBrain : public Brain, public EventListener
{
    public:
        PlayerInputBrain(InputState* inputState);
        virtual ~PlayerInputBrain();
        void trigger(InputActions actions);
    protected:
    private:
};

#endif // PLAYERINPUTBRAIN_H
