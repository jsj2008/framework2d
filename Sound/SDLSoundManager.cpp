#include "SDLSoundManager.h"
#include <SDL/SDL_audio.h>
#include <Sound/SoundPlayers/StreamPlayer.h>
#include <Sound/SoundPlayers/TemplateSoundPlayer.h>
#include <Sound/SoundInstance.h>
#include <Sound/SoundInstances/ChimePlayer.h>
#include <Log/Log.h>
#include <cmath>

void audioCallbackForSDL(void *userdata, Uint8 *stream, int len)
{
    static_cast<SDLSoundManager*>(userdata)->streamUpdate(stream, len);
}
SDLSoundManager::SDLSoundManager()
{
    //ctor
    SDL_AudioSpec desired;
    desired.freq = 44100;
    desired.channels = 4;
    desired.samples = 8096;
    desired.userdata = this;
    desired.callback = &audioCallbackForSDL;
    SDL_AudioSpec obtained;
    if (SDL_OpenAudio(&desired, &obtained) == -1)
    {
        /// This throws an exception out, which is caught outside of this constructor
        g_Log.error(std::string("SDL audio initialisation failed: ") + SDL_GetError());
    }
    mutex = SDL_CreateMutex();
    SDL_PauseAudio(0);
    soundActions.push_back(new StreamPlayer("chimes.wav"));
    soundActions.push_back(new TemplateSoundPlayer<ChimePlayer>());
    soundAction(0);

    int wtf = 32;
    bufferSize = 8096*4*wtf;
    buffer = new unsigned char[bufferSize];
    bufferOffset = 0;
}

SDLSoundManager::~SDLSoundManager()
{
    //dtor
    SDL_DestroyMutex(mutex);
    while (!soundActions.empty())
    {
        delete soundActions.back();
    }
}

void SDLSoundManager::soundAction(unsigned int _action, unsigned int _volume)
{
    SDL_LockMutex(mutex);
    SoundInstance* instance = soundActions[_action]->activate(this, _volume);
    if (instance != nullptr)
    {
        soundInstances.push_back(instance);
    }
    SDL_UnlockMutex(mutex);
}

void SDLSoundManager::poly_streamUpdate(unsigned char* _stream, int _length)
{
    SDL_LockMutex(mutex);
    if (_length > bufferSize && false)
    {
        /*unsigned int oldBufferSize = bufferSize;
        memcpy(_stream, buffer, bufferSize);

        delete[] buffer;
        buffer = new unsigned char[_length];
        bufferSize = _length;*/

        /// Agh whatever
        throw -1;

    }
    else
    {
        /*bool spliced = false;
        int length = _length;
        if (bufferOffset + _length > bufferSize)
        {
            length = bufferSize - bufferOffset;
            spliced = true;
        }
        memcpy(_stream, buffer + bufferOffset, length);
        impl_streamUpdate(buffer + bufferOffset, length);

        if (spliced)
        {
            bufferOffset = _length - length;
            memcpy(_stream + length, buffer, bufferOffset);
            impl_streamUpdate(buffer, bufferOffset);
        }
        else bufferOffset += length;*/
        impl_streamUpdate(_stream, _length);
    }
    SDL_UnlockMutex(mutex);
}

void SDLSoundManager::impl_streamUpdate(unsigned char* _stream, int _length)
{
    memset(_stream, 0, _length);
    for (unsigned int i = 0; i < soundInstances.size(); i++)
    {
        if (!soundInstances[i]->update(_stream , _length))
        {
            delete soundInstances[i];
            soundInstances[i] = soundInstances.back();
            soundInstances.pop_back();
            i--;
        }
    }// */
}







