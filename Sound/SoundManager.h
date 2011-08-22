#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundPlayer;
class SoundInstance;

#define MAX_VOLUME 128

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        virtual void soundAction(unsigned int _action, unsigned int _volume = MAX_VOLUME)=0;
        virtual void streamUpdate(unsigned char* _stream, int _length)=0;
    protected:
    private:
};

#endif // SOUNDMANAGER_H
