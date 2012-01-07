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
#include <Graphics/Camera/FreeCamera.h>
#include <Networking/Client/SinglePlayerGameServer.h>
#include <SDL/SDL.h>

PlayMode::PlayMode()
{
    //ctor
    type = Bubble::eSuctionBubbleType;
    mCamera = nullptr;
    playerOneBrain = nullptr;
    activeLevel = nullptr;
    SingletonEventHandler<PlayerOneCreated>::singleton().registerListener(this, eBlockQueue);

    FreeCamera* mFreeCamera = new FreeCamera();
    mCamera = mFreeCamera;
    g_GraphicsManager.setCamera(mCamera);
    //server = new SinglePlayerGameServer;
}

PlayMode::~PlayMode()
{
    //dtor
    SingletonEventHandler<PlayerOneCreated>::singleton().unregisterListener(this, eBlockQueue);
    //delete server;
}

void PlayMode::setLevel(Level* _level)
{
    if (activeLevel != nullptr)
    {
        delete activeLevel; /// FIXME this should just detach
    }
    attachChild(_level);
    activeLevel = _level;
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
    if (playerOneBrain)
        playerOneBrain->activate();
    return true;
}


bool PlayMode::update()
{
    bool running = true;
    if (GameServerInterface::singleton()->update())
    {
        CEGUI::EventArgs args;
        activate(args);
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
    FactoryParameters params(nullptr);
    params.add<BodyPart*>("body", entity->getRootBody());
    mCamera = activeLevel->getFactories()->useFactory<Camera>("BodyCameraFactory", &params, this);
    playerOneBrain = static_cast<PlayerInputBrain*>(entity->getBrain());
    return true;
}
