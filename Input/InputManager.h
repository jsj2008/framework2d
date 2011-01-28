#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL/SDL_keysym.h>
enum Actions
{
    eUp,
    eDown,
    eLeft,
    eRight,
    eActionsMax
};
class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        bool processInput();
    protected:
    private:
        SDLKey* controls;
};

#endif // INPUTMANAGER_H
