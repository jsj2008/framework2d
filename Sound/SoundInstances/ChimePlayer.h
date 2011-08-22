#ifndef CHIMEPLAYER_H
#define CHIMEPLAYER_H

#include <Sound/SoundInstance.h>

class ChimePlayer : public SoundInstance
{
    public:
        ChimePlayer(unsigned int _volume);
        ~ChimePlayer();
        bool update(unsigned char* _streamSize, int _length); /// Returns true if still active
    protected:
    private:
        unsigned int timeRemaining;
        unsigned int frequency;
        unsigned int currentOffset;
        unsigned int currentVolume;
        unsigned int volume;
};

#endif // CHIMEPLAYER_H
