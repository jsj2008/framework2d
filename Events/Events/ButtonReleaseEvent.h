#ifndef BUTTONRELEASEEVENT_H
#define BUTTONRELEASEEVENT_H

#include <Events/InstanceEvents/InstanceEvent.h>


class ButtonReleaseEvent : public InstanceEvent<ButtonReleaseEvent>
{
    public:
        ButtonReleaseEvent(unsigned int _button);
        virtual ~ButtonReleaseEvent();
        unsigned int getButton(){return button;}
    protected:
    private:
        unsigned int button;
};

#endif // BUTTONRELEASEEVENT_H
