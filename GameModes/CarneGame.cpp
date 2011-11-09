#include "CarneGame.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <Input/InputManager.h>
#include <Graphics/GraphicsManager.h>
#include <AI/PlayerInputBrain.h>
#include <Entities/AIEntity.h>
#include <Entities/TileMap.h>
#include <Box2D/Box2D.h>

CarneGame::CarneGame()
{
    //ctor
    mCamera = nullptr;
}

CarneGame::~CarneGame()
{
    //dtor
}
void CarneGame::buttonUp(Vec2i mouse, unsigned char button)
{
    Vec2f position = playerBrain->mEntity->getPosition();
    Vec2f direction = mouse.ScreenToWorldSpace()-position;
    direction.Normalize();
    //g_TileMap->destroy(position,direction);
}

bool CarneGame::activate(const CEGUI::EventArgs& args)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != nullptr)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    assert(playerBrain);
    playerBrain->activate();
    return true;
}

