#include "EditorMode.h"
#include "GeometryEditorMode.h"
#include "GeometryEditor.h"
#include <Input/InputState.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include "StateSwitcher.h"

EditorMode::EditorMode()
{
    //ctor
    GameMode* modes[2];
    mInputState = new InputState;
    FreeCamera* mFreeCamera = new FreeCamera(mInputState);
    mCamera = mFreeCamera;

    modes[0] = new GeometryEditorMode(mFreeCamera);
    modes[1] = NULL;

    Rect rect(0,0,500,100);
    ClickEvent* selectionBox = new StateSwitcher(rect,1,modes);

    mInputState->registerEvent(selectionBox);
    modes[0]->registerEvent(selectionBox);
    //modes[1]->registerEvent(selectionBox);

    g_InputManager.setInputState(mInputState);
}

EditorMode::~EditorMode()
{
    //dtor
}
