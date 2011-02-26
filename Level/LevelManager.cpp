#include "LevelManager.h"
#include <Level/Level.h>

LevelManager g_LevelManager;
LevelManager::LevelManager()
{
    //ctor
    level = new Level();
}

LevelManager::~LevelManager()
{
    //dtor
}
