#include "EditorMode.h"
#include "GeometryEditorMode.h"
#include "GeometrySelectorMode.h"
#include "ItemSpawnerMode.h"
#include <Input/InputState.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Game.h>
#include "StateSwitcher.h"
#define NUM_MODES 4
EditorMode::EditorMode()
{
    //ctor
    GameMode* modes[NUM_MODES];
    mInputState = new InputState;
    FreeCamera* mFreeCamera = new FreeCamera(mInputState);
    mCamera = mFreeCamera;

    modes[0] = new GeometryEditorMode(mFreeCamera);
    modes[1] = new GeometrySelectorMode(mFreeCamera);
    modes[2] = new ItemSpawnerMode(mFreeCamera);
    modes[3] = g_Game.getGameMode(ePlayGameMode);

    Rect rect(0,0,500,100);
    ClickEvent* selectionBox = new StateSwitcher(rect,NUM_MODES,this,modes);

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
}
