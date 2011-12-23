#ifndef NULLSOUNDMANAGER_H
#define NULLSOUNDMANAGER_H

#include <Sound/SoundManager.h>


class NullSoundManager : public SoundManager
{
    public:
        NullSoundManager();
        virtual ~NullSoundManager();
        void soundAction(unsigned int _action, unsigned int _volume = MAX_VOLUME);
        void poly_streamUpdate(unsigned char* _stream, int _length);
    protected:
    private:
};

#endif // NULLSOUNDMANAGER_H
