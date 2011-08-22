#ifndef STREAMINSTANCE_H
#define STREAMINSTANCE_H

#include <Sound/SoundInstance.h>
class StreamPlayer;

class StreamInstance : public SoundInstance
{
    public:
        StreamInstance(StreamPlayer* _streamPlayer, unsigned int _volume);
        virtual ~StreamInstance();
        bool update(unsigned char* _stream, int _length); /// Returns true if still active
    protected:
    private:
        StreamPlayer* streamPlayer;
        unsigned int bufferPosition;
        unsigned int volume;
};

#endif // STREAMINSTANCE_H
