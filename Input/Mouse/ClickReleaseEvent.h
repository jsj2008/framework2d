#ifndef CLICKRELEASEEVENT_H
#define CLICKRELEASEEVENT_H

#include "InputContext.h"

class ClickReleaseEvent: public InputContext
{
    public:
        ClickReleaseEvent();
        virtual ~ClickReleaseEvent();
        virtual void click(Vec2i mouse, unsigned char button)=0;
    protected:
    private:
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
};

#endif // CLICKRELEASEEVENT_H
