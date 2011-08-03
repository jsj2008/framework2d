#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/GraphicsManager.h>
#include <Game.h>
#include <Level/Level.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 4
EditorMode::EditorMode(Level* _editing, InputContext* _playMode)
{
    //ctor
    editing = _editing;
    InputContext* modes[NUM_MODES];
    FreeCamera* mFreeCamera = new FreeCamera();
    mCamera = mFreeCamera;
    g_GraphicsManager.setCamera(mCamera);

    modes[0] = new DynamicEditor(mFreeCamera, this);
    modes[1] = new JointEditor(mFreeCamera, this);
    modes[2] = new GeometrySelector(mFreeCamera, this);
    modes[3] = _playMode;

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

PhysicsManager* EditorMode::getActiveWorld()
{
    return editing->getWorld();
}
Level* EditorMode::getActiveLevel()
{
    return editing;
}
