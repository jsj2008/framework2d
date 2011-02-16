#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL/SDL_keysym.h>
class EventListener;
enum InputActions
{
    eUp,
    eDown,
    eLeft,
    eRight,
    eInputActionsMax
};
extern class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        bool processInput();
        void registerEvent(EventListener* event, InputActions action);
    protected:
    private:
        struct ControlStruct
        {
            ControlStruct(SDLKey _key){key = _key;event = 0;}
            SDLKey key;
            EventListener* event;
        };
        ControlStruct* controls;
}g_InputManager;

#endif // INPUTMANAGER_H
