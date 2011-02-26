#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H

#include <Input/Mouse/ClickReleaseEvent.h>
#include <vector>
#include <Factory/CrateDef.h>
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
        std::vector<CrateDef> crateDefs;
        void addElement();
};

#endif // ITEMSPAWNER_H
