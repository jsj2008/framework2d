#include "BubbleDrawEvent.h"
#include <Factory/FactoryList.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactoryList.h>

BubbleDrawEvent::BubbleDrawEvent(SelectionBox* _selectionBox)
{
    //ctor
    selectionBox = _selectionBox;
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
    Vec2f position = startPos.ScreenToWorldSpace();
    float radius = (position-mouse.ScreenToWorldSpace()).Length();
    if (radius != 0.0f)
    {
        FactoryParameters parameters;
        parameters.add<Vec2f>("position",position);
        parameters.add<float>("radius",radius);
        parameters.add<std::string>("materialName","defaultBubble");
        //def.type = (Bubble::BubbleType)selectionBox->getCurrentSelection();
        g_AbstractFactoryList.useFactory("suctionBubble",&parameters);
    }
}

