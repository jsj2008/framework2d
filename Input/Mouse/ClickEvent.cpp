#include "ClickEvent.h"

Rect::Rect(int _x, int _y, int _x2, int _y2)
{
    x = _x;
    y = _y;
    x2 = _x2;
    y2 = _y2;
}
bool Rect::contained(int mouseX, int mouseY)
{
    return (mouseX > x && mouseX < x2 && mouseY > y && mouseY < y2);
}
ClickEvent::ClickEvent(const Rect& _Rect)
:mRect(_Rect)
{
    //ctor
}

ClickEvent::~ClickEvent()
{
    //dtor
}
