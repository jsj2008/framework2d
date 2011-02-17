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

bool ClickDragEvent::buttonDown(int mouseX, int mouseY)
{
    if (mRect.contained(mouseX, mouseY))
    {
        startXPos = mouseX;
        startYPos = mouseY;
        start();
        return true;
    }
    else return false;
}
