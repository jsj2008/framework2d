#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

class SDLSoundManager;
class SoundInstance;

class SoundPlayer
{
    public:
        SoundPlayer();
        virtual ~SoundPlayer();
        virtual SoundInstance* activate(SDLSoundManager* _manager, unsigned int _volume)=0;
    protected:
    private:
};

#endif // SOUNDPLAYER_H
