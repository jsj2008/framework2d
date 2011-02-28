#include "ClickEvent.h"
#include <Graphics/GraphicsManager.h>

Rect::Rect(int _x, int _y, int _x2, int _y2)
{
    x = _x;
    y = _y;
    desiredx2 = _x2;
    desiredy2 = _y2;
    Vec2i resolution = g_GraphicsManager.getResolution();
    x2 = (desiredx2 > resolution.x)? resolution.x : desiredx2;
    y2 = (desiredx2 > resolution.y)? resolution.y : desiredy2;
}
bool Rect::contained(Vec2i mouse)
{
    return (mouse.x > x && mouse.x < x2 && mouse.y > y && mouse.y < y2);
}
void Rect::changeResolution(Vec2i newResolution)
{
    x2 = desiredx2;// > newResolution.x)? newResolution.x : desiredx2;
    y2 = desiredy2;// > newResolution.y)? newResolution.y : desiredy2;
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

void ClickEvent::changeResolution(Vec2i newResolution)
{
    mRect.changeResolution(newResolution);
}
