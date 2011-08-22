#include "StaticSoundManager.h"
#include <Sound/SoundManager.h>

StaticSoundManager::StaticSoundManager()
{
    //ctor
}

StaticSoundManager::~StaticSoundManager()
{
    //dtor
}

void StaticSoundManager::init()
{
    soundManager = new SoundManager();
}

void StaticSoundManager::quit()
{
    delete soundManager;
    soundManager = nullptr;
}

SoundManager* StaticSoundManager::soundManager = nullptr;
