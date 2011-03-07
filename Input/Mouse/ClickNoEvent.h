#ifndef CLICKNOEVENT_H
#define CLICKNOEVENT_H

#include <Input/Mouse/InputContext.h>


class ClickNoEvent : public InputContext
{
    public:
        ClickNoEvent();
        virtual ~ClickNoEvent();
        void buttonDown(Vec2i mouse, unsigned char button){}
        void mouseMove(Vec2i mouse){}
        void buttonUp(Vec2i mouse, unsigned char button){}
    protected:
    private:
};

#endif // CLICKNOEVENT_H
