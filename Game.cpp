#include "Game.h"

#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Entities/EntityFactory.h>
#include <GameModes/PlayMode.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/LevelManager.h>
#include <Graphics/Camera/FreeCamera.h>
#include <cstring>
#include <iostream>
using namespace std;
Game g_Game;
void Game::init()
{
    //ctor
    g_Timer.init();
    g_Timer.pause();
    g_EntityFactory.init();
    g_PhysicsManager.init();

    //editorMode = new EditorMode;
    mGameModes[ePlayGameMode] = new PlayMode;
    mGameModes[eEditorGameMode] = new EditorMode;


    b2Vec2 initialPosition(0,-10);
    CreatureDef player;
    player.dimensions.Set(2,2);
    player.texture = 1;
    player.type = ePlayerInputBrainType;
    unsigned int playerInt = g_EntityFactory.addEntityDef(player);
    Entity* entity = g_EntityFactory.createEntity(playerInt,initialPosition);

    ((PlayMode*)mGameModes[ePlayGameMode])->setBody(entity->mBody);

    gameModeStack.push(NULL);
    set(NULL,mGameModes[eEditorGameMode]);
    //set(NULL,mGameModes[ePlayGameMode]);

    initialPosition.Set(0,10);
    cout << "EntityFactoryDef " << sizeof(EntityFactoryDef) << endl;
    cout << "EntityType " << sizeof(EntityType) << endl;
    cout << "EntityFactoryDef::EntityDef " << sizeof(EntityFactoryDef::EntityDef) << endl;
    cout << "PhysicsFactoryDef " << sizeof(PhysicsFactoryDef) << endl;
    cout << "GraphicsFactoryDef " << sizeof(GraphicsFactoryDef) << endl;

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
            g_PhysicsManager.render();
            g_InputManager.render();
        }
        g_GraphicsManager.endScene();
    }
    g_LevelManager.saveLevel("default");
    g_PhysicsManager.clear();
}
