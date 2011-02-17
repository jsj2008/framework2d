#ifndef CLICKDRAGEVENT_H
#define CLICKDRAGEVENT_H

#include "ClickEvent.h"


class ClickDragEvent : public ClickEvent
{
    public:
        ClickDragEvent(const Rect& _Rect);
        virtual ~ClickDragEvent();
        virtual void start()=0;
        ///void mouseMove(int mouseX, int mouseY); Override these instead
        ///void buttonUp(int mouseX, int mouseY);
    protected:
        int startXPos, startYPos;
    private:
        bool buttonDown(int mouseX, int mouseY);
};

#endif // CLICKDRAGEVENT_H
