#include "SoundManager.h"
#include <SDL/SDL_audio.h>
#include <Sound/SoundPlayers/StreamPlayer.h>
#include <Sound/SoundPlayers/TemplateSoundPlayer.h>
#include <Sound/SoundInstance.h>
#include <Sound/SoundInstances/ChimePlayer.h>
#include <cmath>
#include <iostream> /// FIXME
using namespace std;

void audioCallbackForSDL(void *userdata, Uint8 *stream, int len)
{
    static_cast<SoundManager*>(userdata)->streamUpdate(stream, len);
}
SoundManager::SoundManager()
{
    //ctor
    mutex = SDL_CreateMutex();
    SDL_AudioSpec desired;
    desired.freq = 44100;
    desired.channels = 4;
    desired.samples = 8096;
    desired.userdata = this;
    desired.callback = &audioCallbackForSDL;
    SDL_AudioSpec obtained;
    if (SDL_OpenAudio(&desired, &obtained) == -1)
    {
        cout << SDL_GetError() << endl;
        throw -1;
    }
    SDL_PauseAudio(0);
    soundActions.push_back(new StreamPlayer("chimes.wav"));
    soundActions.push_back(new TemplateSoundPlayer<ChimePlayer>());
    soundAction(1);
}

SoundManager::~SoundManager()
{
    //dtor
    SDL_DestroyMutex(mutex);
}

void SoundManager::soundAction(unsigned int _action)
{
    //cout << "Executing sound action " << _action << endl;
    SDL_LockMutex(mutex);
    SoundInstance* instance = soundActions[_action]->activate(this);
    if (instance != nullptr)
    {
        soundInstances.push_back(instance);
    }
    SDL_UnlockMutex(mutex);
    //cout << "Executed" << endl;
}

void SoundManager::streamUpdate(unsigned char* _stream, int _length)
{
    cout << "Updating streams" << endl;
    SDL_LockMutex(mutex);
    memset(_stream, 0, _length);
    for (unsigned int i = 0; i < soundInstances.size(); i++)
    {
        if (!soundInstances[i]->update(_stream, _length))
        {
            delete soundInstances[i];
            soundInstances[i] = soundInstances.back();
            soundInstances.pop_back();
            i--;
        }
    }
    SDL_UnlockMutex(mutex);
    cout << "Updated streams" << endl;
}









