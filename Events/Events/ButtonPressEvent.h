#ifndef BUTTONPRESSEVENT_H
#define BUTTONPRESSEVENT_H

#include <Events/InstanceEvents/InstanceEvent.h>


class ButtonPressEvent : public InstanceEvent<ButtonPressEvent>
{
    public:
        ButtonPressEvent(unsigned int _button);
        virtual ~ButtonPressEvent();
        unsigned int getButton(){return button;}
    protected:
    private:
        unsigned int button;
};

#endif // BUTTONPRESSEVENT_H
