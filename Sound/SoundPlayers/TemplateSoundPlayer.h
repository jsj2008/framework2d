#ifndef TEMPLATESOUNDPLAYER_H
#define TEMPLATESOUNDPLAYER_H

#include <Sound/SoundPlayer.h>

template <typename soundInstance>
class TemplateSoundPlayer : public SoundPlayer
{
    public:
        TemplateSoundPlayer();
        ~TemplateSoundPlayer();
        SoundInstance* activate(SoundManager* _manager);
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
SoundInstance* TemplateSoundPlayer<soundInstance>::activate(SoundManager* _manager)
{
    return new soundInstance();
}

#endif // TEMPLATESOUNDPLAYER_H
