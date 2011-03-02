#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL/SDL_events.h>
#include <vector>
#include <Types/Vec2i.h>
class EventListener;
class ClickEvent;
class TextBox;

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
        void changeResolution(const Vec2i newResolution);
        void activeTextBox(TextBox* _textBox);
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
        TextBox* textBox;
};

#endif // INPUTSTATE_H
