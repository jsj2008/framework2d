#include "Game.h"
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <GameModes/PlayMode.h>
#include <GameModes/ShooterGame.h>
#include <GameModes/CarneGame.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <AI/AIManager.h>
#include <AI/CharacterController.h>
#include <SharedContent/ContentManager.h>
#include <SharedContent/WeaponContent.h>
#include <AbstractFactory/AbstractFactories.h>

#include <AbstractFactory/Factories/ExplosionFactory.h>
#include <AbstractFactory/Factories/ProjectileFactory.h>
#include <AbstractFactory/Factories/ParticleFactory.h>
#include <AbstractFactory/Factories/CrateFactory.h>
#include <AbstractFactory/Factories/LevelGeometryFactory.h>
#include <AbstractFactory/Factories/AIEntityFactory.h>
#include <AbstractFactory/Factories/TileFactory.h>
#include <AbstractFactory/Factories/TileMapFactory.h>
#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Graphics/SkinFactory/StaticSkinFactory.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Physics/Factories/CharacterBodyFactory.h>

#include <AI/BrainFactory/AllBrainFactories.h>

#include <cstring>
#include <iostream>
using namespace std;
Game g_Game;
Game::Game()
{
}
#include <SDL/SDL_timer.h>
void Game::init()
{
    //ctor
    g_Timer.init();
    g_Timer.pause();
    /*AbstractFactories::registerFactoryType<Entity, ExplosionFactory>();
    AbstractFactories::registerFactoryType<Entity, ProjectileFactory>();
    AbstractFactories::registerFactoryType<Entity, ParticleFactory>();
    AbstractFactories::registerFactoryType<Entity, CrateFactory>();
    AbstractFactories::registerFactoryType<Entity,  LevelGeometryFactory>();
    AbstractFactories::registerFactoryType<Entity, AIEntityFactory>();
    AbstractFactories::registerFactoryType<Entity, TileMapFactory>();
    AbstractFactories::registerFactoryType<Entity, TileFactory>();*/
    AbstractFactories::registerFactoryType<Entity, BubbleFactory<SuctionBubble>>();
    AbstractFactories::registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();

    /*AbstractFactories::registerFactoryType<Skin, StaticSkinFactory>();

    AbstractFactories::registerFactoryType<b2Body, CharacterBodyFactory>();

    AbstractFactories::registerFactoryType<Brain, PlayerInputBrainFactory>();*/

    AbstractFactories::init();
    //AbstractFactories::getSingleton().getFactoryList<Brain>().init();
    //AbstractFactories::getSingleton().getFactoryList<Skin>().init();
    //AbstractFactories::getSingleton().getFactoryList<b2Body>().init();

    g_ContentManager.addSharedContent(new WeaponContent("pistol"));
    g_PhysicsManager.init();

    mGameModes[ePlayGameMode] = new ShooterGame;
    mGameModes[eEditorGameMode] = new EditorMode;

    g_LevelManager.loadLevel("default");
    FactoryParameters params;
    AbstractFactories::useFactory<Entity>("player",&params);
    //g_LevelManager.addBody("tiles",&params);

    CEGUI::EventArgs args;
    mGameModes[eEditorGameMode]->activate(args);
    mGameModes[ePlayGameMode]->activate(args);

    g_AIManager.finalisePathfinding();


    g_Timer.unPause();
}
Game::~Game()
{
    //dtor
}
InputContext* Game::getGameMode(GameModes mode)
{
    return mGameModes[mode];
}
#include <GL/gl.h>
void Game::run()
{
    bool running = true;
    while (running)
    {
        if (g_PhysicsManager.update())
        {
            running = g_InputManager.processInput();
        }
        g_GraphicsManager.beginScene();
        g_PhysicsManager.render();
        g_InputManager.render();
        g_LevelManager.tempRender();
        g_AIManager.tempRender();
        SDL_Delay(5);
        g_GraphicsManager.endScene();
    }
    g_LevelManager.saveLevel("default");
    //delete mGameModes[ePlayGameMode];
    //delete mGameModes[eEditorGameMode];
    g_PhysicsManager.clear();
}




















