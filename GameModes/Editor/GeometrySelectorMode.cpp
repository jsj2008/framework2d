#include "GeometrySelectorMode.h"
#include "GeometrySelector.h"
#include <Input/InputState.h>
#include <Graphics/Camera/FreeCamera.h>

GeometrySelectorMode::GeometrySelectorMode(FreeCamera* camera)
{
    //ctor
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    mCamera = camera;
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(new GeometrySelector(fullScreen));
}

GeometrySelectorMode::~GeometrySelectorMode()
{
    //dtor
}
