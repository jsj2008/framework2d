#include "ItemSpawner.h"
#include <Input/Mouse/SelectionBox.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Level/LevelManager.h>
#include <Input/InputState.h>

ItemSpawner::ItemSpawner(FreeCamera* camera, const Rect& _Rect)
:ClickReleaseEvent(_Rect),
crateDefs({CrateDef(4,2,""),CrateDef(1,1,"player")})
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect rect(0,100,200,200);
    selectionBox = new SelectionBox(rect,{"GeometrySelector"});
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(this);

    mInputState->registerEvent(selectionBox);
}

ItemSpawner::~ItemSpawner()
{
    //dtor
}

void ItemSpawner::click(Vec2i mouse, unsigned char button)
{
    int which = selectionBox->getCurrentSelection();
    if (which == selectionBox->getNumElements())
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
    CrateDef def;
    cout << "Box width?" << endl;
    cin >> def.width;

    cout << "Box height?" << endl;
    cin >> def.height;

    cout << "Material name?" << endl;
    cin >> def.materialName;

    crateDefs.push_back(def);
}
