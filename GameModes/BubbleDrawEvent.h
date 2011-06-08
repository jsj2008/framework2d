#ifndef BUBBLEDRAWEVENT_H
#define BUBBLEDRAWEVENT_H

#include <Input/Mouse/ClickDragEvent.h>
class SelectionBox;

class BubbleDrawEvent : public ClickDragEvent
{
    public:
        BubbleDrawEvent(SelectionBox* _selectionBox);
        virtual ~BubbleDrawEvent();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
        SelectionBox* selectionBox;
};

#endif // BUBBLEDRAWEVENT_H
