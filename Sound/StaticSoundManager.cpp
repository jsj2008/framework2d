#include "StaticSoundManager.h"
#include <Sound/SDLSoundManager.h>
#include <Sound/NullSoundManager.h>

using namespace std;

StaticSoundManager::StaticSoundManager()
{
    //ctor
    soundManager = nullptr;
}

StaticSoundManager::~StaticSoundManager()
{
    //dtor
}

void StaticSoundManager::init()
{
    try
    {
        soundManager = new SDLSoundManager();
    }
    catch (...)
    {
        soundManager = new NullSoundManager;
    }
}
void StaticSoundManager::quit()
{
    delete soundManager;
    soundManager = nullptr;
}

SoundManager* StaticSoundManager::soundManager = nullptr;
