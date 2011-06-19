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
    mCamera = NULL;
}

CarneGame::~CarneGame()
{
    //dtor
}
extern TileMap* g_TileMap; /// FIXME
void CarneGame::buttonUp(Vec2i mouse, unsigned char button)
{
    /*Vec2f position = mouse.ScreenToWorldSpace();
    playerBrain->mEntity->fireAt(position);*/
    Vec2f position = playerBrain->mEntity->mBody->GetPosition();
    Vec2f direction = mouse.ScreenToWorldSpace()-position;
    direction.Normalize();
    g_TileMap->destroy(position,direction);
}

void CarneGame::setBody(b2Body* body, PlayerInputBrain* _playerBrain)
{
    mCamera = new PhysicsCamera(body);
    playerBrain = _playerBrain;
    playerBrain->trigger(eUp);
}

bool CarneGame::activate(const CEGUI::EventArgs& args)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != NULL)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    assert(playerBrain);
    playerBrain->activate();
    return true;
}

