#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <Input/InputManager.h>

class EventListener
{
    public:
        EventListener(InputState* inputState);
        virtual ~EventListener();
        virtual void trigger(InputActions action)=0;
    protected:
    private:
};

#endif // EVENTLISTENER_H
