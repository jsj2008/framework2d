#include "SoundManager.h"
#include <UI/BeatDisplay.h>

SoundManager::SoundManager()
{
    //ctor
    beatDisplay = new BeatDisplay;
    /// Normalise lastValues
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::streamUpdate(unsigned char* _stream, int _length)
{
    poly_streamUpdate(_stream, _length);
    beatDisplay->updateStream(_stream, _length);
    beatDisplay->render();
}

