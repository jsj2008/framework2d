#include "Game.h"
#include <Graphics/GraphicsManager.h>
#include <Physics/PhysicsManager.h>
#include <Input/InputManager.h>
#include <GameModes/PlayMode.h>
#include <GameModes/ShooterGame.h>
#include <GameModes/CarneGame.h>
#include <Timer.h>
#include <GameModes/Editor/EditorMode.h>
#include <Level/Level.h>
#include <GameModes/Editor/Undo/UndoStack.h>
#include <Graphics/Camera/FreeCamera.h>
#include <AI/AIManager.h>
#include <AI/CharacterController.h>
#include <SharedContent/ContentManager.h>
#include <AbstractFactory/AbstractFactories.h>

#include <AbstractFactory/Factories/BubbleFactory.h>
#include <Entities/Bubbles/AllBubbles.h>
#include <Sound/StaticSoundManager.h>
#include <Sound/SoundManager.h>

#include <cstring>

using namespace std;
Game g_Game;
Game::Game()
{
}
void Game::init()
{
    //ctor
    Timer::global()->init();
    Timer::global()->pause();

    g_GraphicsManager.init();
    StaticSoundManager::init();

    //EditorMode* typedMode = new EditorMode(new ShooterGame());
    ShooterGame* typedMode = new ShooterGame();
    typedMode->init();
    gameMode = typedMode;

    CEGUI::EventArgs args;
    typedMode->activate(args);


    UndoStack::global().init();

    Timer::global()->unpause();
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




















