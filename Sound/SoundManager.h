#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundPlayer;
class SoundInstance;
class BeatDisplay;

#define MAX_VOLUME 128

class SoundManager
{
#define FREQUENCIES 8
    public:
        SoundManager();
        virtual ~SoundManager();
        virtual void soundAction(unsigned int _action, unsigned int _volume = MAX_VOLUME)=0;
        void streamUpdate(unsigned char* _stream, int _length);
    protected:
    private:
        virtual void poly_streamUpdate(unsigned char* _stream, int _length)=0;
        BeatDisplay* beatDisplay;
};

#endif // SOUNDMANAGER_H
