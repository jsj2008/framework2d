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

#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Entities/Bubbles/AllBubbles.h>


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
    level = new Level("default");

    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<SuctionBubble>>();
    AbstractFactories::global().registerFactoryType<Entity, BubbleFactory<UpwardsGravityBubble>>();
    AbstractFactories::global().init(level->getWorld());

    g_ContentManager.addSharedContent(new WeaponContent("pistol"));

    level->loadLevel();
    FactoryParameters params;
    ShooterGame* playMode = new ShooterGame;
    playMode->setCamera(AbstractFactories::global().useFactory<Camera>("BodyCameraFactory",&params));

    editor = new EditorMode(level, playMode);

    CEGUI::EventArgs args;
    editor->activate(args);

    g_AIManager.init(level->getWorld());
    g_AIManager.finalisePathfinding();

    UndoStack::global().init();
    g_Timer.unPause();
}
Game::~Game()
{
    //dtor
}
#include <GL/gl.h>
void Game::run()
{
    bool running = true;
    while (running)
    {
        if (level->update())
        {
            running = g_InputManager.processInput();
        }
        g_GraphicsManager.beginScene();
        g_InputManager.render();
        level->render();
        g_AIManager.tempRender();
        SDL_Delay(5);
        g_GraphicsManager.endScene();
    }
    delete level;
    //delete mGameModes[ePlayGameMode];
    //delete mGameModes[eEditorGameMode];
}




















