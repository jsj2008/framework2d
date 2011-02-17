#include "Game.h"

#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Entities/EntityFactory.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <GL/gl.h>
#include <cstring>
#include <iostream>
using namespace std;
Game::Game()
{
    //ctor
    mPhysicsManager = new PhysicsManager();
    g_EntityFactory.init(mPhysicsManager);

    b2Vec2 initialPosition(0,-10);
    CreatureDef player;
    player.dimensions.Set(2,2);
    player.texture = 0;
    player.type = ePlayerInputBrainType;
    unsigned int playerInt = g_EntityFactory.addEntityDef(player);
    Entity* entity = g_EntityFactory.createEntity(playerInt,initialPosition);
    g_EntityFactory.setCameraTarget(entity);
    entities.push(entity);

    initialPosition.Set(0,10);
    PlatformDef platform;
    platform.addPoint(b2Vec2(-10,0));
    platform.addPoint(b2Vec2(10,0));
    platform.addPoint(b2Vec2(0,10));
    unsigned int platformInt = g_EntityFactory.addEntityDef(platform);
    entity = g_EntityFactory.createEntity(platformInt,initialPosition);
    entities.push(entity);
    cout << "EntityFactoryDef " << sizeof(EntityFactoryDef) << endl;
    cout << "EntityType " << sizeof(EntityType) << endl;
    cout << "EntityFactoryDef::EntityDef " << sizeof(EntityFactoryDef::EntityDef) << endl;
    cout << "PhysicsFactoryDef " << sizeof(PhysicsFactoryDef) << endl;
    cout << "GraphicsFactoryDef " << sizeof(GraphicsFactoryDef) << endl;

    editorMode = new EditorMode;
    g_Timer.init();
    mPhysicsManager->init();
}
Entity* g_Temp = NULL;
Game::~Game()
{
    //dtor
}
void Game::run()
{
    bool running = true;
    while (running)
    {
        g_GraphicsManager.beginScene();
        if (mPhysicsManager->update())
        {
            running = g_InputManager.processInput();
            for (int i = 0; i < entities.size(); i++)
            {
                entities[i]->render();
                entities[i]->update();
            }
            if (g_Temp != NULL)
            {
                g_Temp->render();
                g_Temp->update();
            }
        }
        g_GraphicsManager.endScene();
    }
}
