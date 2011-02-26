#include "ItemSpawner.h"
#include <Input/Mouse/SelectionBox.h>
#include <Level/LevelManager.h>

ItemSpawner::ItemSpawner(const Rect& _Rect, SelectionBox* _selectionBox)
:ClickReleaseEvent(_Rect),
crateDefs({CrateDef(4,2,""),CrateDef(1,1,"player")})
{
    //ctor
    selectionBox = _selectionBox;
    selectionBox->setNumElements(3);
}

ItemSpawner::~ItemSpawner()
{
    //dtor
}

void ItemSpawner::click(Vec2i mouse, unsigned char button)
{
    int which = selectionBox->getCurrentSelection();
    if (which == selectionBox->getNumElements()-1)
    {
        addElement();
    }
    else
    {
        Vec2f worldSpace = mouse.ScreenToWorldSpace();
        crateDefs[which].position = worldSpace;
        g_LevelManager.addCrate(&crateDefs[which]);
    }
}
#include <iostream>
using namespace std;
/// Should replace this with a graphical editor at some point FIXME
void ItemSpawner::addElement()
{
    selectionBox->setNumElements(selectionBox->getNumElements()+1);
    CrateDef def;
    cout << "Box width?" << endl;
    cin >> def.width;

    cout << "Box height?" << endl;
    cin >> def.height;

    cout << "Material name?" << endl;
    cin >> def.materialName;

    crateDefs.push_back(def);
}
