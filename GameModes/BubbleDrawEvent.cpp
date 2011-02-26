#include "BubbleDrawEvent.h"
#include <Factory/FactoryList.h>

BubbleDrawEvent::BubbleDrawEvent(const Rect& _Rect, SelectionBox* _selectionBox)
:ClickDragEvent(_Rect)
{
    //ctor
    selectionBox = _selectionBox;
    def.setMaterial("defaultBubble");
}

BubbleDrawEvent::~BubbleDrawEvent()
{
    //dtor
}

void BubbleDrawEvent::start(unsigned char button)
{

}
void BubbleDrawEvent::mouseMove(Vec2i mouse)
{

}
void BubbleDrawEvent::buttonUp(Vec2i mouse, unsigned char button)
{
    def.position = startPos.ScreenToWorldSpace();
    def.radius = (def.position-mouse.ScreenToWorldSpace()).Length();
    if (def.radius != 0.0f)
    {
        g_FactoryList.useFactory(&def, FactoryList::eBubbleFactory);
    }
}
