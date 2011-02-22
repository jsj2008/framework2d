#include "ClickDragEvent.h"

ClickDragEvent::ClickDragEvent(const Rect& _Rect)
:ClickEvent(_Rect)
{
    //ctor
}

ClickDragEvent::~ClickDragEvent()
{
    //dtor
}

bool ClickDragEvent::buttonDown(Vec2i mouse, unsigned char button)
{
    if (mRect.contained(mouse))
    {
        startPos = mouse;
        start(button);
        return true;
    }
    else return false;
}
