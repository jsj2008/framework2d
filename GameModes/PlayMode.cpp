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
#include <Entities/AIEntity.h>
#include <Networking/Client/SinglePlayerGameServer.h>
#include <SDL/SDL.h>

PlayMode::PlayMode()
{
    //ctor
    type = Bubble::eSuctionBubbleType;
    mCamera = nullptr;
    playerOneBrain = nullptr;
    SingletonEventHandler<PlayerOneCreated>::singleton().registerListener(this, eBlockQueue);
    //server = new SinglePlayerGameServer;
}

PlayMode::~PlayMode()
{
    //dtor
    SingletonEventHandler<PlayerOneCreated>::singleton().unregisterListener(this, eBlockQueue);
    //delete server;
}

void PlayMode::start(unsigned char button)
{

}
void PlayMode::mouseMove(Vec2i mouse)
{

}

bool PlayMode::activate(const CEGUI::EventArgs& args)
{
    g_InputManager.setActiveEvent(this);
    if (mCamera != nullptr)
    {
        g_GraphicsManager.setCamera(mCamera);
        mCamera->activate();
    }
    assert(playerOneBrain);
    playerOneBrain->activate();
    return true;
}


bool PlayMode::update()
{
    bool running = true;
    if (GameServerInterface::singleton()->update())
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

bool PlayMode::trigger(PlayerOneCreated* event)
{
    AIEntity* entity = event->getPlayer();
    FactoryParameters params;
    params.add<b2Body*>("body", entity->getBody());
    mCamera = AbstractFactories::global().useFactory<Camera>("BodyCameraFactory", &params);
    playerOneBrain = entity->getBrain();
    return true;
}
