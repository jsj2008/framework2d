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
    EntityFactoryDef def(ePlayerEntityType);
    def.physicsDef.bodyDef.type = b2_dynamicBody;
    def.physicsDef.fixtureShape.SetAsBox(1,1);
    def.graphicsDef.graphicsDef.staticSkinDef.texture = 0;

    b2Vec2 initialPosition(0,0);
    entity = dummyFactory.entityFactory(def,initialPosition);
    dummyFactory.setCameraTarget(entity);
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
        entity->render();
        mPhysicsManager->update();
        mGraphicsManager->endScene();
    }
}
