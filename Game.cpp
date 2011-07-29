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
#include <GameModes/Editor/Undo/UndoStack.h>
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

    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<SuctionBubble>>();
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();
    AbstractFactories::global().init();

    g_ContentManager.addSharedContent(new WeaponContent("pistol"));
    g_PhysicsManager.init();

    mGameModes[ePlayGameMode] = new ShooterGame;

    g_LevelManager.loadLevel("default");
    FactoryParameters params;
    AbstractFactories::global().useFactory<Camera>("BodyCameraFactory",&params);
    //g_LevelManager.addBody("tiles",&params);

    mGameModes[eEditorGameMode] = new EditorMode;

    CEGUI::EventArgs args;
    mGameModes[eEditorGameMode]->activate(args);
    mGameModes[ePlayGameMode]->activate(args);

    g_AIManager.finalisePathfinding();

    UndoStack::global().init();
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




















