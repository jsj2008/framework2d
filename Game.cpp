#include "Game.h"
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <GameModes/PlayMode.h>
#include <GameModes/ShooterGame.h>
#include <GameModes/CarneGame.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/LevelManager.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <Graphics/Camera/FreeCamera.h>
#include <AI/AIManager.h>
#include <AI/CharacterController.h>
#include <SharedContent/ContentManager.h>
#include <SharedContent/WeaponContent.h>
#include <AbstractFactory/AbstractFactories.h>

#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Entities/Bubbles/AllBubbles.h>

#include <cstring>
#include <iostream>
using namespace std;
Game g_Game;
Game::Game()
{
}
void Game::init()
{
    //ctor
    g_Timer.init();
    g_Timer.pause();

    g_ContentManager.addSharedContent(new WeaponContent("pistol"));

    EditorMode* typedMode = new EditorMode(new ShooterGame());
    gameMode = typedMode;

    CEGUI::EventArgs args;
    typedMode->activate(args);


    UndoStack::global().init();
    g_Timer.unPause();
}
Game::~Game()
{
    //dtor
}
#include <GL/gl.h>
void Game::run()
{
    while (gameMode->update());
    delete gameMode;
}




















