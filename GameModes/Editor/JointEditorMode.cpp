#include "JointEditorMode.h"
#include "JointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Input/Mouse/SelectionBox.h>

JointEditorMode::JointEditorMode(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    Rect fullScreen(0,0,10000,10000);
    mInputState->registerEvent(new JointEditor(fullScreen));
    Rect rect(0,400,300,450);
    SelectionBox* selectionBox = new SelectionBox(rect,{NULL});
    mInputState->registerEvent(selectionBox);
}

JointEditorMode::~JointEditorMode()
{
    //dtor
}