#include "ClickReleaseEvent.h"

ClickReleaseEvent::ClickReleaseEvent()
{
    //ctor
}

ClickReleaseEvent::~ClickReleaseEvent()
{
    //dtor
}

void ClickReleaseEvent::buttonDown(Vec2i mouse, unsigned char button)
{
}
void ClickReleaseEvent::mouseMove(Vec2i mouse)
{

}
void ClickReleaseEvent::buttonUp(Vec2i mouse, unsigned char button)
{
    click(mouse, button);
}
