#include "StreamPlayer.h"
#include <SDL/SDL_audio.h>
#include <cstring>
#include <Sound/SoundPlayers/StreamInstance.h>
#include <string>

StreamPlayer::StreamPlayer(const char* _filename)
{
    //ctor
    audioBuffer = nullptr;
    referenceCount = 0;
    filename = _filename;
}

StreamPlayer::~StreamPlayer()
{
    //dtor
}

SoundInstance* StreamPlayer::activate(SDLSoundManager* _manager, unsigned int _volume)
{
    if (audioBuffer == nullptr)
    {
        SDL_AudioSpec spec;
        SDL_AudioSpec* actualSpec = SDL_LoadWAV((std::string("Resources/Audio/") + filename).c_str(), &spec, &audioBuffer, &bufferLength);
    }
    referenceCount++;
    return new StreamInstance(this, _volume);
}

bool StreamPlayer::update(unsigned char* _stream, unsigned int _begin, unsigned int _length)
{
    if (_begin + _length < bufferLength)
    {
        memcpy(_stream, audioBuffer + _begin, _length);
        return true;
    }
    else
    {
        //memcpy()
        return false;
    }
}
