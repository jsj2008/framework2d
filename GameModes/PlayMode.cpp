#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Entities/Bubble.h>
#include <Factory/FactoryList.h>
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <AI/PlayerInputBrain.h>

PlayMode::PlayMode()
{
    //ctor
    def.setMaterial("defaultBubble");
    mCamera = NULL;
}

PlayMode::~PlayMode()
{
    //dtor
}

void PlayMode::start(unsigned char button)
{

}
void PlayMode::mouseMove(Vec2i mouse)
{

}
void PlayMode::buttonUp(Vec2i mouse, unsigned char button)
{
    def.setPosition(startPos.ScreenToWorldSpace());
    def.radius = (def.getPosition()-mouse.ScreenToWorldSpace()).Length();
    def.type = (Bubble::BubbleType)1;
    if (def.radius != 0.0f)
    {
        g_FactoryList.useFactory(def, eBubbleFactory);
    }
}
void PlayMode::setBody(b2Body* body, PlayerInputBrain* _playerBrain)
{
    mCamera = new PhysicsCamera(body);
    playerBrain = _playerBrain;
}

bool PlayMode::activate(const CEGUI::EventArgs& args)
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

