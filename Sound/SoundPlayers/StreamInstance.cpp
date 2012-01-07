#include "StreamInstance.h"
#include <Sound/SoundPlayers/StreamPlayer.h>

StreamInstance::StreamInstance(StreamPlayer* _streamPlayer, unsigned int _volume)
{
    //ctor
    streamPlayer = _streamPlayer;
    volume = _volume;
}

StreamInstance::~StreamInstance()
{
    //dtor
    streamPlayer->streamInstanceDestroyed();
    //StaticSoundManager::getSoundManager()->soundAction(0);
}

bool StreamInstance::update(unsigned char* _stream, int _length)
{
    unsigned int newPosition = bufferPosition + _length;
    bool ret = streamPlayer->update(_stream, bufferPosition, _length);
    bufferPosition = newPosition;
    return ret;
}
