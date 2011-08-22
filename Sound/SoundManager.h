#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <vector>
#include <SDL/SDL.h>
class SoundPlayer;
class SoundInstance;

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        void soundAction(unsigned int _action);
        void streamUpdate(unsigned char* _stream, int _length);
        void addSoundPlayer(SoundPlayer* _soundPlayer);
    protected:
    private:
        std::vector<SoundPlayer*> soundActions;
        std::vector<SoundInstance*> soundInstances;
        SDL_mutex* mutex;
};

#endif // SOUNDMANAGER_H
