#include "Game.h"
#include <Factory/FactoryDefList.h>
#include <Factory/CrateDef.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <GameModes/PlayMode.h>
#include <GameModes/ShooterGame.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Factory/BubbleDef.h>
#include <AI/AIManager.h>
#include <AI/CharacterController.h>
#include <SharedContent/ContentManager.h>
#include <SharedContent/WeaponContent.h>
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
    g_ContentManager.addSharedContent(new WeaponContent("pistol"));
    g_PhysicsManager.init();

    mGameModes[ePlayGameMode] = new ShooterGame;
    mGameModes[eEditorGameMode] = new EditorMode;

    g_LevelManager.loadLevel("default");
    g_FactoryDefList.useFactoryDef(0);

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




















