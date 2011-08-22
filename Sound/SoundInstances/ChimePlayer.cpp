#include "ChimePlayer.h"
#include <cmath>

ChimePlayer::ChimePlayer()
{
    //ctor
    timeRemaining = 300000;
    frequency = 120;
    currentOffset = 0;
    currentVolume = 128;
}

ChimePlayer::~ChimePlayer()
{
    //dtor
}

bool ChimePlayer::update(unsigned char* _stream, int _length)
{
    unsigned int end = _length;
    bool ret = true;
    if (timeRemaining < end)
    {
        end = timeRemaining;
        ret = false;
    }
    else
    {
        timeRemaining -= _length;
    }
    for (unsigned int i = 0; i < end; i++)
    {
        currentOffset++;
        if (currentOffset % 1000 == 0)
        {
            currentVolume--;
            if (currentVolume == 0)
                return false;
        }
        _stream[i] = sin(currentOffset/frequency)*currentVolume;
    }
    return ret;
}
