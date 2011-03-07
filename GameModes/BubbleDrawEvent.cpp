#include "BubbleDrawEvent.h"
#include <Factory/FactoryList.h>
/*
BubbleDrawEvent::BubbleDrawEvent(SelectionBox* _selectionBox)
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
    def.setPosition(startPos.ScreenToWorldSpace());
    def.radius = (def.getPosition()-mouse.ScreenToWorldSpace()).Length();
    def.type = (Bubble::BubbleType)selectionBox->getCurrentSelection();
    if (def.radius != 0.0f)
    {
        g_FactoryList.useFactory(def, eBubbleFactory);
    }
}
*/
