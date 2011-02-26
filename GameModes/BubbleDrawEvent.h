#ifndef BUBBLEDRAWEVENT_H
#define BUBBLEDRAWEVENT_H

#include <Input/Mouse/ClickDragEvent.h>
#include <Factory/BubbleDef.h>
class SelectionBox;

class BubbleDrawEvent : public ClickDragEvent
{
    public:
        BubbleDrawEvent(const Rect& _Rect, SelectionBox* _selectionBox);
        virtual ~BubbleDrawEvent();
        void start(unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
    protected:
    private:
        SelectionBox* selectionBox;
        BubbleDef def;
};

#endif // BUBBLEDRAWEVENT_H
