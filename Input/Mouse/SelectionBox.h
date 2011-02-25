#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include "ClickReleaseEvent.h"


class SelectionBox : public ClickReleaseEvent
{
    public:
        SelectionBox(const Rect& _Rect, int _numElements);
        virtual ~SelectionBox();
        void click(Vec2i mouse, unsigned char button);
        void render();
        int getCurrentSelection(){return currentSelection;}
    protected:
        virtual void selectionTrigger(){}
        int currentSelection;
    private:
        int numElements;
        int div;
};

#endif // SELECTIONBOX_H
