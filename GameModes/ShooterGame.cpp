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
#include <Level/XmlDataSaver.h>
#include <AI/AIManager.h>

ShooterGame::ShooterGame()
{
    //ctor
    AbstractFactories::registerFactoryType<Entity, BubbleFactory<SuctionBubble>>(); /// FIXME these should be in the bubble game
    AbstractFactories::registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();

    XmlResourceProvider provider;
    LevelLoader loader(&provider);
    LevelData* data = loader.load("Levels.xml/Level1/Level");
    {
        //XmlDataSaver saver;
        //data->save(&saver, &std::string("Levels.xml/Level1/Level"));
    }
    setLevel(data->build());
    //activeLevel = new Level("default");
    //AbstractFactories::global().init(); /// FIXME these need to not be global

    mCamera = nullptr;

    //activeLevel->loadLevel();
    g_AIManager.init(getLevel()->getWorld()); /// FIXME this shouildn't be global
    g_AIManager.finalisePathfinding();

    FactoryParameters params(data->getFactories());
    params.add<unsigned short>("entityKey", 0);
    PlayerOneCreated event(static_cast<AIEntity*>(getLevel()->getFactories()->useFactory<Entity>("PlayerFactory",&params, this)));
    event.trigger();
}

ShooterGame::~ShooterGame()
{
    //dtor
    delete getLevel(); /// FIXME not managed properly
}

void ShooterGame::buttonUp(Vec2i mouse, unsigned char button) /// FIXME this needs to be done in a player controller grabber
{
    //Vec2f position = mouse.ScreenToWorldSpace();
    //playerBrain->mEntity->weaponEnd(position);
}
