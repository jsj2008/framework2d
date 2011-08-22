#ifndef SDLSOUNDMANAGER_H
#define SDLSOUNDMANAGER_H

#include <vector>
#include <SDL/SDL.h>
#include <Sound/SoundManager.h>

class SDLSoundManager : public SoundManager
{
    public:
        SDLSoundManager();
        virtual ~SDLSoundManager();
        void soundAction(unsigned int _action, unsigned int _volume = MAX_VOLUME);
        void streamUpdate(unsigned char* _stream, int _length);
    protected:
    private:
        std::vector<SoundPlayer*> soundActions;
        std::vector<SoundInstance*> soundInstances;
        SDL_mutex* mutex;
};

#endif // SDLSOUNDMANAGER_H
