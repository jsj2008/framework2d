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

    BubbleDef bubble;
    bubble.position = Vec2f(0,0);
    bubble.radius = 5;
    g_FactoryList.useFactory(&bubble,FactoryList::eBubbleFactory);

    ((PlayMode*)mGameModes[ePlayGameMode])->setBody(entity->mBody);

    set(NULL,mGameModes[ePlayGameMode]);
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
void Game::run()
{
    bool running = true;
    while (running)
    {
        g_GraphicsManager.beginScene();
        if (g_PhysicsManager.update())
        {
            running = g_InputManager.processInput();
        }
        g_InputManager.render();
        g_PhysicsManager.render();
        g_GraphicsManager.endScene();
    }
    g_LevelManager.saveLevel("default");
    g_PhysicsManager.clear();
}




















