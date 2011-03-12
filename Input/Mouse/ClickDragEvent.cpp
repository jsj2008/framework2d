#include "ClickDragEvent.h"

ClickDragEvent::ClickDragEvent()
{
    //ctor
}

ClickDragEvent::~ClickDragEvent()
{
    //dtor
}

void ClickDragEvent::buttonDown(Vec2i mouse, unsigned char button)
{
    startPos = mouse;
    start(button);
}
