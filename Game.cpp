#include "Game.h"
#include <Factory/FactoryList.h>
#include <Factory/CrateDef.h>
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <GameModes/PlayMode.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <Factory/BubbleDef.h>
#include <cstring>
#include <iostream>
using namespace std;
Game g_Game;
Game::Game()
///:gameModeStack({NULL}) Compiler segmentation fault? wtf?
{
    gameModeStack.push(NULL);
}
#include <SDL/SDL_timer.h>
void Game::init()
{
    //ctor
    g_Timer.init();
    g_Timer.pause();
    g_PhysicsManager.init();

    //editorMode = new EditorMode;
    mGameModes[ePlayGameMode] = new PlayMode;
    mGameModes[eEditorGameMode] = new EditorMode;

    CrateDef def;
    def.position = Vec2f(0,0);
    def.width = 2;
    def.height = 2;
    Entity* entity = g_FactoryList.useFactory(&def,FactoryList::ePlayerFactory);

    ((PlayMode*)mGameModes[ePlayGameMode])->setBody(entity->mBody);

    set(NULL,mGameModes[eEditorGameMode]);

    g_LevelManager.loadLevel("default");

    g_Timer.unPause();
}
Game::~Game()
{
    //dtor
}
GameMode* Game::getGameMode(GameModes mode)
{
    return mGameModes[mode];
}
void Game::set(GameMode* root, GameMode* mode)
{
    GameMode* mTop = gameModeStack.top();
    while (mTop != root)
    {
        gameModeStack.pop();
        mTop = gameModeStack.top();
    }
    if (mode == NULL)
    {
        mTop->set();
    }
    else
    {
        gameModeStack.push(mode);
        mode->set();
    }
}
#include <GL/gl.h>
void Game::run()
{
    bool running = true;
    while (running)
    {
        g_GraphicsManager.beginScene();
        g_LevelManager.renderBackground();
        if (g_PhysicsManager.update())
        {
            running = g_InputManager.processInput();
        }
        g_PhysicsManager.render();
        glColor4f(1,1,1,0.5);
        g_InputManager.render();
        glColor4f(1,1,1,1);
        g_LevelManager.tempRender();
        SDL_Delay(30);
        g_GraphicsManager.endScene();
    }
    g_LevelManager.saveLevel("default");
    //delete mGameModes[ePlayGameMode];
    //delete mGameModes[eEditorGameMode];
    g_PhysicsManager.clear();
}




















