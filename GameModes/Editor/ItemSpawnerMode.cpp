#include "ItemSpawnerMode.h"
#include "ItemSpawner.h"
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>

ItemSpawnerMode::ItemSpawnerMode(FreeCamera* camera)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(new ItemSpawner(fullScreen));
}

ItemSpawnerMode::~ItemSpawnerMode()
{
    //dtor
}
