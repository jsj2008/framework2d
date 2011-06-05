#include "AIEntitySpawner.h"
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>

AIEntitySpawner::AIEntitySpawner(FreeCamera* camera)
:def("player",2,2,eZombieBrainType,"pistol")
{
    //ctor
    mCamera = camera;
}

AIEntitySpawner::~AIEntitySpawner()
{
    //dtor
}

void AIEntitySpawner::click(Vec2i mouse, unsigned char button)
{
    def.position = mouse.ScreenToWorldSpace();
    g_LevelManager.addBody(def);
}
