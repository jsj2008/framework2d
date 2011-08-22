#include "StreamInstance.h"
#include <Sound/SoundPlayers/StreamPlayer.h>
#include <Sound/SoundManager.h>
#include <Sound/StaticSoundManager.h>
#include <iostream>
using namespace std;

StreamInstance::StreamInstance(StreamPlayer* _streamPlayer)
{
    //ctor
    streamPlayer = _streamPlayer;
}

StreamInstance::~StreamInstance()
{
    //dtor
    streamPlayer->streamInstanceDestroyed();
    StaticSoundManager::getSoundManager()->soundAction(0);
}

bool StreamInstance::update(unsigned char* _stream, int _length)
{
    cout << "Updating instance" << endl;
    unsigned int newPosition = bufferPosition + _length;
    bool ret = streamPlayer->update(_stream, bufferPosition, _length);
    bufferPosition = newPosition;
    cout << "Updated instance, returning " << ret << endl;
    return ret;
}
