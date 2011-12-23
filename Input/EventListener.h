#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <Input/InputManager.h>

class EventListener
{
    public:
        EventListener();
        virtual ~EventListener();
        virtual void trigger(InputActions action, bool _pressed)=0;
    protected:
    private:
};

#endif // EVENTLISTENER_H
