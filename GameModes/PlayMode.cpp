#include "PlayMode.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <GameModes/BubbleDrawEvent.h>
#include <Entities/Bubble.h>
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <AI/PlayerInputBrain.h>
#include <Level/Level.h>
#include <AbstractFactory/FactoryParameters.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AI/AIManager.h>
#include <Networking/Client/SinglePlayerGameServer.h>
#include <SDL/SDL.h>

PlayMode::PlayMode()
{
    //ctor
    type = Bubble::eSuctionBubbleType;
    mCamera = nullptr;
    playerBrain = nullptr;
    Events::global().registerListener(this, eBlockQueue);
    //server = new SinglePlayerGameServer;
    server = GameServerInterface::singleton();
}

PlayMode::~PlayMode()
{
    //dtor
    Events::global().unregisterListener(this, true);
    //delete server;
}

void PlayMode::start(unsigned char button)
{

}
void PlayMode::mouseMove(Vec2i mouse)
{

}
void PlayMode::setCamera(Camera* _camera)
{
    mCamera = _camera;
}

bool PlayMode::activate(const CEGUI::EventArgs& args)
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


bool PlayMode::update()
{
    bool running = true;
    if (server->update())
    {
        activeLevel->tick();
    }
    running = g_InputManager.processInput();
    g_GraphicsManager.beginScene();
    g_InputManager.render();
    activeLevel->render();
    g_AIManager.tempRender();
    //SDL_Delay(5);
    g_GraphicsManager.endScene();
    return running;
}
