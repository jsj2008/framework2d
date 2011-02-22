#include "ClickReleaseEvent.h"

ClickReleaseEvent::ClickReleaseEvent(const Rect& _Rect)
:ClickEvent(_Rect)
{
    //ctor
}

ClickReleaseEvent::~ClickReleaseEvent()
{
    //dtor
}

bool ClickReleaseEvent::buttonDown(Vec2i mouse, unsigned char button)
{
    return mRect.contained(mouse);
}
void ClickReleaseEvent::mouseMove(Vec2i mouse)
{

}
void ClickReleaseEvent::buttonUp(Vec2i mouse, unsigned char button)
{
    if (mRect.contained(mouse))
    {
        click(mouse, button);
    }
}
