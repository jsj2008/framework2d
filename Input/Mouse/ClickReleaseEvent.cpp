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

bool ClickReleaseEvent::buttonDown(int mouseX, int mouseY)
{
    return mRect.contained(mouseX, mouseY);
}
void ClickReleaseEvent::mouseMove(int mouseX, int mouseY)
{

}
void ClickReleaseEvent::buttonUp(int mouseX, int mouseY)
{
    if (mRect.contained(mouseX, mouseY))
    {
        click(mouseX, mouseY);
    }
}
