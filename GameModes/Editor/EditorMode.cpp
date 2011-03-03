#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputState.h>
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/Primitives/Icon.h>
#include <Game.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 6
EditorMode::EditorMode()
{
    //ctor
    GameMode* modes[NUM_MODES];
    mInputState = new InputState;
    FreeCamera* mFreeCamera = new FreeCamera(mInputState);
    mCamera = mFreeCamera;
    Rect fullscreen(0,0,10000,10000);

    modes[0] = new GeometrySelector(mFreeCamera,fullscreen);
    modes[1] = new GeometryEditor(mFreeCamera,fullscreen);
    modes[2] = new ItemSpawner(mFreeCamera,fullscreen);
    modes[3] = new JointEditor(mFreeCamera,fullscreen);
    modes[4] = new ParallaxEditor(mFreeCamera,fullscreen);
    modes[5] = g_Game.getGameMode(ePlayGameMode);

    Rect rect(0,0,500,100);
    Vec2i dimensions(500/NUM_MODES,100);
    selectionBox = new EditorStateSwitcher(rect,{"GeometrySelector","GeometryEditor","ItemSpawner","JointEditor","ParallaxEditor","TestPlay"},this,modes);

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
