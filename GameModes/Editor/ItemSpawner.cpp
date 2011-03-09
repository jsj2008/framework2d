#include "ItemSpawner.h"
#include <Graphics/Camera/FreeCamera.h>
#include <GameModes/Editor/EditorStateSwitcher.h>
#include <GameModes/Editor/CrateSpawner.h>
#include <GameModes/Editor/AIEntitySpawner.h>

ItemSpawner::ItemSpawner(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
}

void ItemSpawner::init()
{
    mCamera->activate();
    modes[0] = new CrateSpawner((FreeCamera*)mCamera);
    modes[1] = new AIEntitySpawner((FreeCamera*)mCamera);
    stateSwitcher = new EditorStateSwitcher("ItemSpawner/TabControl",{"CrateSpawner","AIEntitySpawner"}, modes);
    registerEvent(stateSwitcher);

    for (unsigned int i = 0; i < NUM_ITEM_SPAWNERS; i++)
    {
        modes[i]->init();
    }
}
ItemSpawner::~ItemSpawner()
{
    //dtor
    delete stateSwitcher;
}
void ItemSpawner::registerEvent(InputContext* event)
{
    for (unsigned int i = 0; i < NUM_ITEM_SPAWNERS; i++)
    {
        //modes[i]->registerEvent(event);
    }
}
bool ItemSpawner::activate(const CEGUI::EventArgs&)
{
    stateSwitcher->eventShow();
    g_InputManager.setActiveEvent(this);
    return true;
}
