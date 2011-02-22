#include "ClickEvent.h"

Rect::Rect(int _x, int _y, int _x2, int _y2)
{
    x = _x;
    y = _y;
    x2 = _x2;
    y2 = _y2;
}
bool Rect::contained(Vec2i mouse)
{
    return (mouse.x > x && mouse.x < x2 && mouse.y > y && mouse.y < y2);
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
