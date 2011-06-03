#include "Game.h"
#include <Factory/FactoryList.h>
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
    g_PhysicsManager.init();

    mGameModes[ePlayGameMode] = new ShooterGame;
    mGameModes[eEditorGameMode] = new EditorMode;

    AIEntityDef def;
    def.setPosition(Vec2f(0,-20));
    def.setMaterial("player");
    def.width = 2;
    def.height = 2;
    def.aiType = ePlayerInputBrainType;
    g_LevelManager.loadLevel("default");
    g_FactoryList.useFactory(def,eAIEntityFactory);

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




















