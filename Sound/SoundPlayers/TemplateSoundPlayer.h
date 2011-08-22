#ifndef TEMPLATESOUNDPLAYER_H
#define TEMPLATESOUNDPLAYER_H

#include <Sound/SoundPlayer.h>

template <typename soundInstance>
class TemplateSoundPlayer : public SoundPlayer
{
    public:
        TemplateSoundPlayer();
        ~TemplateSoundPlayer();
        SoundInstance* activate(SDLSoundManager* _manager, unsigned int _volume);
    protected:
    private:
};

template <typename soundInstance>
TemplateSoundPlayer<soundInstance>::TemplateSoundPlayer()
{
    //ctor
}

template <typename soundInstance>
TemplateSoundPlayer<soundInstance>::~TemplateSoundPlayer()
{
    //dtor
}
template <typename soundInstance>
SoundInstance* TemplateSoundPlayer<soundInstance>::activate(SDLSoundManager* _manager, unsigned int _volume)
{
    return new soundInstance(_volume);
}

#endif // TEMPLATESOUNDPLAYER_H
