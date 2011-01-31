#include "Game.h"

#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <Entities/EntityFactory.h>
#include <GL/gl.h>
#include <iostream>
#include <cstring>
using namespace std;
Entity* entity;
Game::Game()
{
    //ctor
    mGraphicsManager = new GraphicsManager();
    mInputManager = new InputManager();
    mPhysicsManager = new PhysicsManager();

    EntityFactory dummyFactory(mGraphicsManager,mPhysicsManager);
    EntityFactoryDef player(ePlayerEntityType);

    player.physicsDef.bodyDef.type = b2_dynamicBody;
    player.physicsDef.shape.SetAsBox(2,1);
    player.graphicsDef.graphicsDef.staticSkinDef.texture = 0;

    EntityFactoryDef crate = EntityFactoryDef(eCrateEntityType);
    crate.physicsDef.bodyDef.type = b2_staticBody;
    crate.physicsDef.shape.SetAsBox(2,1);
    crate.graphicsDef.graphicsDef.staticSkinDef.texture = 0;

    b2Vec2 initialPosition(0,0);
    entity = dummyFactory.entityFactory(player,initialPosition);
    dummyFactory.setCameraTarget(entity);
    entities.push(entity);
    initialPosition.Set(0,50);
    entity = dummyFactory.entityFactory(crate,initialPosition);
    entities.push(entity);
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
    while (mInputManager->processInput())
    {
        mGraphicsManager->beginScene();
        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2i(100,100);
        glVertex2i(200,100);
        glVertex2i(200,200);
        glVertex2i(100,200);
        glEnd();
        //entity->render();
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->render();
        }
        mPhysicsManager->update();
        mGraphicsManager->endScene();
    }
}
