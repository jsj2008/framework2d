#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <Input/Mouse/ClickReleaseEvent.h>
class SelectionBox;

class ItemSpawner : public ClickReleaseEvent
{
    public:
        ItemSpawner(const Rect& _Rect, SelectionBox* _selectionBox);
        virtual ~ItemSpawner();
        void click(Vec2i mouse, unsigned char button);
    protected:
    private:
        SelectionBox* selectionBox;
};

#endif // ITEMSPAWNER_H
