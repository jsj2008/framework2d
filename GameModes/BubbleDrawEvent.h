#ifndef BUBBLEDRAWEVENT_H
#define BUBBLEDRAWEVENT_H

#include <Input/Mouse/ClickDragEvent.h>
class SelectionBox;
template <typename Product>
class AbstractFactoryBase;
class Entity;

class BubbleDrawEvent : public ClickDragEvent
{
    public:
        BubbleDrawEvent(SelectionBox* _selectionBox, AbstractFactoryBase<Entity>* _bubbleFactory);
        virtual ~BubbleDrawEvent();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
        SelectionBox* selectionBox;
        AbstractFactoryBase<Entity>* bubbleFactory;
};

#endif // BUBBLEDRAWEVENT_H
