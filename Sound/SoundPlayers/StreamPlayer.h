#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <Sound/SoundPlayer.h>

class StreamPlayer : public SoundPlayer
{
    public:
        StreamPlayer(const char* _filename);
        virtual ~StreamPlayer();
        SoundInstance* activate(SoundManager* _manager);
        bool update(unsigned char* _stream, unsigned int _begin, unsigned int _length); /// Returns false if buffer has ended
        void streamInstanceDestroyed(){referenceCount--;}
    protected:
    private:
        const char* filename;
        unsigned char* audioBuffer;
        unsigned int bufferLength;
        unsigned short referenceCount;
};

#endif // STREAMPLAYER_H
