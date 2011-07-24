#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/GraphicsManager.h>
#include <Game.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 4
EditorMode::EditorMode()
{
    //ctor
    InputContext* modes[NUM_MODES];
    FreeCamera* mFreeCamera = new FreeCamera();
    mCamera = mFreeCamera;
    g_GraphicsManager.setCamera(mCamera);

    modes[0] = new DynamicEditor(mFreeCamera);
    modes[1] = new JointEditor(mFreeCamera);
    modes[2] = new GeometrySelector(mFreeCamera);
    modes[3] = g_Game.getGameMode(ePlayGameMode);

    Vec2i dimensions(500/NUM_MODES,100);
    selectionBox = new EditorStateSwitcher("Editor/TabControl",{"DynamicEditor","JointEditor","GeometrySelector","TestPlay"},modes);

    for (unsigned int i = 0; i < NUM_MODES; i++)
    {
        modes[i]->init();
    }
}

EditorMode::~EditorMode()
{
    //dtor
    delete selectionBox;
}
