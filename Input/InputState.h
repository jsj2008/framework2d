#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL/SDL_keysym.h>
#include <vector>

class EventListener;
class ClickEvent;
enum InputActions
{
    eUp,
    eLeft,
    eDown,
    eRight,
    ePlus, /// Need to make these the scroll wheel
    eMinus,
    eInputActionsMax
};

class InputState
{
    public:
        InputState();
        virtual ~InputState();
        virtual bool processInput();
        void registerEvent(EventListener* event, InputActions action);
        void registerEvent(ClickEvent* event);
        void render();
    protected:
    private:
        struct ControlStruct
        {
            ControlStruct(SDLKey _key){key = _key;event = 0;}
            ControlStruct(char _key){key = SDLKey(_key);event = 0;}
            SDLKey key;
            EventListener* event;
        };
        ControlStruct* controls;
        std::vector<ClickEvent*> clickEvents;
        ClickEvent* activeEvent;
};

#endif // INPUTSTATE_H
