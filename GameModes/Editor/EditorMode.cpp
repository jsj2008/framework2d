#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/GraphicsManager.h>
#include <Game.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 7
EditorMode::EditorMode()
{
    //ctor
    InputContext* modes[NUM_MODES];
    FreeCamera* mFreeCamera = new FreeCamera();
    mCamera = mFreeCamera;
    g_GraphicsManager.setCamera(mCamera);

    modes[0] = new GeometrySelector(mFreeCamera);
    modes[1] = new GeometryEditor(mFreeCamera);
    modes[2] = new ItemSpawner(mFreeCamera);
    modes[3] = new ParallaxEditor(mFreeCamera);
    modes[4] = new JointEditor(mFreeCamera);
    modes[5] = new DynamicEditor(mFreeCamera);
    modes[6] = g_Game.getGameMode(ePlayGameMode);

    Vec2i dimensions(500/NUM_MODES,100);
    selectionBox = new EditorStateSwitcher("Editor/TabControl",{"GeometrySelector","GeometryEditor","ItemSpawner","ParallaxEditor","JointEditor","DynamicEditor","TestPlay"},modes);

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
