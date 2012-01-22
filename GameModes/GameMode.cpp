#include "GameMode.h"
#include <Graphics/GraphicsManager.h>
#include <Input/InputManager.h>
#include <Level/Level.h>
#include <Filesystem/Filesystem.h>
#include <Game.h>
#include <cassert>

GameMode::GameMode()
:GameObject("game", Filesystem::global())
{
    //ctor
}

GameMode::~GameMode()
{
    //dtor
}

void GameMode::registerActions(GameObjectType* _type)
{
}

bool GameMode::update()
{
    return v_Update();
}

