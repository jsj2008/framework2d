#include "ShooterGame.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <Input/InputManager.h>
#include <Graphics/GraphicsManager.h>
#include <AI/PlayerInputBrain.h>
#include <Entities/AIEntity.h>

ShooterGame::ShooterGame()
{
    //ctor
    def.setMaterial("defaultBubble");
    mCamera = NULL;
}

ShooterGame::~ShooterGame()
{
    //dtor
}

void ShooterGame::buttonUp(Vec2i mouse, unsigned char button)
{
    Vec2f position = mouse.ScreenToWorldSpace();
    playerBrain->mEntity->fireAt(position);
}

void ShooterGame::setBody(b2Body* body, PlayerInputBrain* _playerBrain)
{
    mCamera = new PhysicsCamera(body);
    playerBrain = _playerBrain;
    playerBrain->trigger(eUp);
}

bool ShooterGame::activate(const CEGUI::EventArgs& args)
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

