#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

class SoundManager;
class SoundInstance;

class SoundPlayer
{
    public:
        SoundPlayer();
        virtual ~SoundPlayer();
        virtual SoundInstance* activate(SoundManager* _manager)=0;
    protected:
    private:
};

#endif // SOUNDPLAYER_H
