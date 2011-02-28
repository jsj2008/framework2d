#include "GameMode.h"
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <Input/InputState.h>
#include <Game.h>
#include <cassert>
GameMode::GameMode()
{
    //ctor
    mCamera = NULL;
    mInputState = NULL;
}

GameMode::~GameMode()
{
    //dtor
    delete mInputState;
}

void GameMode::registerEvent(ClickEvent* event)
{
    mInputState->registerEvent(event);
}
void GameMode::set()
{
    assert(mCamera);
    assert(mInputState);
    g_GraphicsManager.setCamera(mCamera);
    g_InputManager.setInputState(mInputState);
}
