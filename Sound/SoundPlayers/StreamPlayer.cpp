#include "StreamPlayer.h"
#include <SDL/SDL_audio.h>
#include <cstring>
#include <Sound/SoundPlayers/StreamInstance.h>
#include <iostream>
using namespace std;

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

SoundInstance* StreamPlayer::activate(SoundManager* _manager)
{
    cout << "Activating player " << this << endl;
    if (audioBuffer == nullptr)
    {
        SDL_AudioSpec spec;
        SDL_AudioSpec* actualSpec = SDL_LoadWAV((std::string("Resources/Audio/") + filename).c_str(), &spec, &audioBuffer, &bufferLength);
    }
    referenceCount++;
    cout << "Activated player" << endl;
    return new StreamInstance(this);
}

bool StreamPlayer::update(unsigned char* _stream, unsigned int _begin, unsigned int _length)
{
    cout << "Updating player" << endl;
    if (_begin + _length < bufferLength)
    {
        memcpy(_stream, audioBuffer + _begin, _length);
    cout << "Player still playing" << endl;
        return true;
    }
    else
    {
        //memcpy()
    cout << "Player finished" << endl;
        return false;
    }
}
