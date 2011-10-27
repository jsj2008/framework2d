#include "BubbleDrawEvent.h"
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactories.h>
#include <Entities/Entity.h>

BubbleDrawEvent::BubbleDrawEvent(SelectionBox* _selectionBox, AbstractFactoryBase<Entity>* _bubbleFactory)
{
    //ctor
    selectionBox = _selectionBox;
    bubbleFactory = _bubbleFactory;
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
        bubbleFactory->use(&parameters);
    }
}

