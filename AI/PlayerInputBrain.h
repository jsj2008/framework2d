#ifndef PLAYERINPUTBRAIN_H
#define PLAYERINPUTBRAIN_H

#include "Brain.h"
#include <Input/EventListener.h>


class PlayerInputBrain : public Brain, public EventListener
{
    public:
        PlayerInputBrain();
        virtual ~PlayerInputBrain();
    protected:
    private:
};

#endif // PLAYERINPUTBRAIN_H
