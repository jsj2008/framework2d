#include "ItemSpawnerMode.h"
#include "ItemSpawner.h"
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Input/Mouse/SelectionBox.h>

ItemSpawnerMode::ItemSpawnerMode(FreeCamera* camera)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect rect(0,100,500,200);
    SelectionBox* selectionBox = new SelectionBox(rect,1);
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(new ItemSpawner(fullScreen,selectionBox));

    mInputState->registerEvent(selectionBox);
}

ItemSpawnerMode::~ItemSpawnerMode()
{
    //dtor
}
