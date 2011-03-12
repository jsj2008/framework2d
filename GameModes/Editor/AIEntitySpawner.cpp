#include "AIEntitySpawner.h"
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>

AIEntitySpawner::AIEntitySpawner(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
    def.set("player",2,2,eZombieBrainType);
}

AIEntitySpawner::~AIEntitySpawner()
{
    //dtor
}

void AIEntitySpawner::click(Vec2i mouse, unsigned char button)
{
    def.setPosition(mouse.ScreenToWorldSpace());
    g_LevelManager.addBody(def);
}
