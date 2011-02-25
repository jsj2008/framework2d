#include "ItemSpawner.h"
#include <Input/Mouse/SelectionBox.h>

ItemSpawner::ItemSpawner(const Rect& _Rect, SelectionBox* _selectionBox)
:ClickReleaseEvent(_Rect)
{
    //ctor
    selectionBox = _selectionBox;
}

ItemSpawner::~ItemSpawner()
{
    //dtor
}

void ItemSpawner::click(Vec2i mouse, unsigned char button)
{
    Vec2f position = mouse.ScreenToWorldSpace();
    int which = selectionBox->getCurrentSelection();
}
