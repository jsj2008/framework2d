#ifndef CLICKDRAGEVENT_H
#define CLICKDRAGEVENT_H

#include "InputContext.h"


class ClickDragEvent : public InputContext
{
    public:
        ClickDragEvent();
        virtual ~ClickDragEvent();
        virtual void start(unsigned char button)=0;
        ///void mouseMove(Vec2i mouse); Override these instead
        ///void buttonUp(Vec2i mouse, unsigned char button);
    protected:
        Vec2i startPos;
    private:
        void buttonDown(Vec2i mouse, unsigned char button);
};

#endif // CLICKDRAGEVENT_H
