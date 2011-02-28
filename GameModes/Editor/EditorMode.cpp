#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputState.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/Primitives/Icon.h>
#include <Game.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 5
EditorMode::EditorMode()
{
    //ctor
    GameMode* modes[NUM_MODES];
    mInputState = new InputState;
    FreeCamera* mFreeCamera = new FreeCamera(mInputState);
    mCamera = mFreeCamera;

    modes[0] = new GeometrySelectorMode(mFreeCamera);
    modes[1] = new GeometryEditorMode(mFreeCamera);
    modes[2] = new ItemSpawnerMode(mFreeCamera);
    modes[3] = new JointEditorMode(mFreeCamera);
    modes[4] = g_Game.getGameMode(ePlayGameMode);

    Rect rect(0,0,500,100);
    Vec2i dimensions(500/NUM_MODES,100);
    selectionBox = new EditorStateSwitcher(rect,{
        new Icon("GeometrySelector",dimensions),
        new Icon("GeometryEditor",dimensions),
        new Icon("ItemSpawner",dimensions),
        new Icon("JointEditor",dimensions),
        new Icon("TestPlay",dimensions)
        },this,modes);

    mInputState->registerEvent(selectionBox);
    for (unsigned int i = 0; i < NUM_MODES; i++)
    {
        modes[i]->registerEvent(selectionBox);
    }

    g_InputManager.setInputState(mInputState);
}

EditorMode::~EditorMode()
{
    //dtor
    delete selectionBox;
}
