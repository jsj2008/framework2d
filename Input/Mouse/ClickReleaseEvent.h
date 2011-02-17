#ifndef CLICKRELEASEEVENT_H
#define CLICKRELEASEEVENT_H

#include "ClickEvent.h"

class ClickReleaseEvent: public ClickEvent
{
    public:
        ClickReleaseEvent(const Rect& _Rect);
        virtual ~ClickReleaseEvent();
        virtual void click(int mouseX, int mouseY)=0;
    protected:
    private:
        bool buttonDown(int mouseX, int mouseY);
        void mouseMove(int mouseX, int mouseY);
        void buttonUp(int mouseX, int mouseY);
};

#endif // CLICKRELEASEEVENT_H
