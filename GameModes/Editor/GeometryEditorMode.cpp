#include "GeometryEditorMode.h"
#include "GeometryEditor.h"
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>

GeometryEditorMode::GeometryEditorMode(FreeCamera* camera)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(new GeometryEditor(fullScreen));
}

GeometryEditorMode::~GeometryEditorMode()
{
    //dtor
}
