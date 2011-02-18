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
    mPhysicsManager = new PhysicsManager();
    g_EntityFactory.init(mPhysicsManager);

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

    mGameModes[ePlayGameMode]->set();
    mGameModes[eEditorGameMode]->set();

    initialPosition.Set(0,10);
    cout << "EntityFactoryDef " << sizeof(EntityFactoryDef) << endl;
    cout << "EntityType " << sizeof(EntityType) << endl;
    cout << "EntityFactoryDef::EntityDef " << sizeof(EntityFactoryDef::EntityDef) << endl;
    cout << "PhysicsFactoryDef " << sizeof(PhysicsFactoryDef) << endl;
    cout << "GraphicsFactoryDef " << sizeof(GraphicsFactoryDef) << endl;

    g_Timer.init();
    mPhysicsManager->init();

}
Game::~Game()
{
    //dtor
}
GameMode* Game::getGameMode(GameModes mode)
{
    return mGameModes[mode];
}
void Game::run()
{
    bool running = true;
    g_LevelManager.loadLevel("default");
    while (running)
    {
        g_GraphicsManager.beginScene();
        if (mPhysicsManager->update())
        {
            running = g_InputManager.processInput();
            mPhysicsManager->render();
            g_InputManager.render();
        }
        g_GraphicsManager.endScene();
    }
    g_LevelManager.saveLevel("default");
}
