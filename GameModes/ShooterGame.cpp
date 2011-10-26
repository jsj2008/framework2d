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
#include <Level/XmlResourceProvider.h>
#include <Level/LevelLoader.h>

ShooterGame::ShooterGame()
{
    //ctor
    XmlResourceProvider provider;
    LevelLoader loader(&provider);
    loader.load("Levels.xml/Level1/Level");
    activeLevel = new Level("default");
    AbstractFactories::global().setWorld(activeLevel->getWorld());
    AbstractFactories::global().init(); /// FIXME these need to not be global

    mCamera = nullptr;
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<SuctionBubble>>(); /// FIXME these should be in the bubble game
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();

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
    //playerBrain->mEntity->weaponEnd(position);
}
