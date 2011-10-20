#include "ShooterGame.h"
#include <Graphics/Camera/PhysicsCamera.h>
#include <Input/InputManager.h>
#include <Graphics/GraphicsManager.h>
#include <AI/PlayerInputBrain.h>
#include <Entities/AIEntity.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Level/Level.h>

ShooterGame::ShooterGame()
{
    //ctor
    activeLevel = new Level("default");
    AbstractFactories::global().setWorld(activeLevel->getWorld());
    AbstractFactories::global().init(); /// FIXME these need to not be global

    mCamera = nullptr;
    playerBrain = nullptr;
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<SuctionBubble>>(); /// FIXME these should be in the bubble game
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();

    FactoryParameters params;
    params.add<std::string>("name", "player");
    setCamera(AbstractFactories::global().useFactory<Camera>("BodyCameraFactory",&params)); /// FIXME this needs to be in its own init function
    activeLevel->loadLevel();
}

ShooterGame::~ShooterGame()
{
    //dtor
    delete activeLevel;
}

void ShooterGame::buttonUp(Vec2i mouse, unsigned char button) /// FIXME this needs to be done in a player controller grabber
{
    Vec2f position = mouse.ScreenToWorldSpace();
    playerBrain->mEntity->weaponEnd(position);
}

void ShooterGame::setBody(b2Body* body, PlayerInputBrain* _playerBrain)
{
    mCamera = new PhysicsCamera(body);
    playerBrain = _playerBrain;
    playerBrain->trigger(eUp);
}

/*bool ShooterGame::activate(const CEGUI::EventArgs& args)
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
}*/

bool ShooterGame::trigger(FactoryTypeUsageEvent<Brain, PlayerInputBrainFactory>* event)
{
    playerBrain = static_cast<PlayerInputBrain*>(event->get());
    return true;
}
