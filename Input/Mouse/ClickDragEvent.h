#ifndef CLICKDRAGEVENT_H
#define CLICKDRAGEVENT_H

#include "ClickEvent.h"


class ClickDragEvent : public ClickEvent
{
    public:
        ClickDragEvent(const Rect& _Rect);
        virtual ~ClickDragEvent();
        virtual void start(unsigned char button)=0;
        ///void mouseMove(int mouseX, int mouseY); Override these instead
        ///void buttonUp(int mouseX, int mouseY);
    protected:
        Vec2i startPos;
    private:
        bool buttonDown(Vec2i mouse, unsigned char button);
};

#endif // CLICKDRAGEVENT_H
