#include "AIEntitySpawner.h"
#include <Level/LevelManager.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Graphics/Camera/FreeCamera.h>

AIEntitySpawner::AIEntitySpawner(FreeCamera* camera)
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
    FactoryParameters parameters;
    parameters.add("position",mouse.ScreenToWorldSpace());
    g_LevelManager.addBody("zombie",&parameters);
}
