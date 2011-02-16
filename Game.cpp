#include "Game.h"

#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Entities/EntityFactory.h>
#include <GL/gl.h>
#include <iostream>
#include <cstring>
using namespace std;
Game::Game()
{
    //ctor
    mGraphicsManager = new GraphicsManager();
    mPhysicsManager = new PhysicsManager();

    EntityFactory dummyFactory(mGraphicsManager,mPhysicsManager);

    b2Vec2 initialPosition(40,0);
    CreatureDef player;
    player.dimensions.Set(2,2);
    player.texture = 0;
    player.type = ePlayerInputBrainType;
    unsigned int playerInt = dummyFactory.addEntityDef(player);
    Entity* entity = dummyFactory.createEntity(playerInt,initialPosition);
    dummyFactory.setCameraTarget(entity);
    entities.push(entity);
    initialPosition.Set(0,50);
    //entity = dummyFactory.entityFactory(crate,initialPosition);
    //entities.push(entity);
    cout << "EntityFactoryDef " << sizeof(EntityFactoryDef) << endl;
    cout << "EntityType " << sizeof(EntityType) << endl;
    cout << "EntityFactoryDef::EntityDef " << sizeof(EntityFactoryDef::EntityDef) << endl;
    cout << "PhysicsFactoryDef " << sizeof(PhysicsFactoryDef) << endl;
    cout << "GraphicsFactoryDef " << sizeof(GraphicsFactoryDef) << endl;
}

Game::~Game()
{
    //dtor
}
void Game::run()
{
    while (g_InputManager.processInput())
    {
        mGraphicsManager->beginScene();
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->render();
            entities[i]->update();
        }
        mPhysicsManager->update();
        mGraphicsManager->endScene();
    }
}
