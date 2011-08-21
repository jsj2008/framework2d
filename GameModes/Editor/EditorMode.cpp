#include "EditorMode.h"
#include "AllEditorModes.h"
#include <Input/InputManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Graphics/GraphicsManager.h>
#include <GameModes/ShooterGame.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AI/AIManager.h>
#include <Game.h>
#include <Level/Level.h>
#include "EditorStateSwitcher.h"
#define NUM_MODES 4
EditorMode::EditorMode(PlayMode* _playMode)
{
    //ctor
    activeLevel = _playMode;

    InputContext* modes[NUM_MODES];
    FreeCamera* mFreeCamera = new FreeCamera();
    mCamera = mFreeCamera;
    g_GraphicsManager.setCamera(mCamera);

    modes[0] = new DynamicEditor(mFreeCamera, this);
    modes[1] = new JointEditor(mFreeCamera, this);
    modes[2] = new GeometrySelector(mFreeCamera, this);
    modes[3] = activeLevel;

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
    delete activeLevel;
    delete selectionBox;
}

PhysicsManager* EditorMode::getActiveWorld()
{
    return activeLevel->getLevel()->getWorld();
}
Level* EditorMode::getActiveLevel()
{
    return activeLevel->getLevel();
}
bool EditorMode::update()
{
    return activeLevel->update();
}
