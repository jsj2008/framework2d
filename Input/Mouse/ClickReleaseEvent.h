#ifndef CLICKRELEASEEVENT_H
#define CLICKRELEASEEVENT_H

#include "ClickEvent.h"

class ClickReleaseEvent: public ClickEvent
{
    public:
        ClickReleaseEvent(const Rect& _Rect);
        virtual ~ClickReleaseEvent();
        virtual void click(Vec2i mouse, unsigned char button)=0;
    protected:
    private:
        bool buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
};

#endif // CLICKRELEASEEVENT_H
