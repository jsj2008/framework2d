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
        void poly_streamUpdate(unsigned char* _stream, int _length);
    protected:
    private:
        void impl_streamUpdate(unsigned char* _stream, int _length);
        std::vector<SoundPlayer*> soundActions;
        std::vector<SoundInstance*> soundInstances;
        SDL_mutex* mutex;
        unsigned char* buffer;
        unsigned int bufferOffset;
        unsigned int bufferSize;
};

#endif // SDLSOUNDMANAGER_H
