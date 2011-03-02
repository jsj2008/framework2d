#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <queue>
#include <SDL/SDL_events.h>
#include <Input/InputState.h>
#include <Types/Vec2i.h>
class EventListener;
class InputGrabber;
class TextBox;

extern class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void cleanup();
        void changeResolution(const Vec2i newResolution);
        bool processInput();
        void registerEvent(EventListener* event, InputActions action);
        void registerGlobalEvent(EventListener* event, InputActions action); /// These are global controls
        void setInputState(InputState* _currentState);
        void activeTextBox(TextBox* _textBox);
        void render();
    protected:
    private:
        InputGrabber* inputGrabber;
        InputState* currentState;
        Vec2i currentResolution;
        unsigned int* globalEventsSizeWhenSeen;
        struct InputStateHistory
        {
            InputStateHistory(InputState* _state, unsigned int _globalEventsSizeWhenSeen){state = _state; globalEventsSizeWhenSeen = _globalEventsSizeWhenSeen;}
            InputState* state;
            unsigned int globalEventsSizeWhenSeen;
        };
        std::vector<InputStateHistory> inputStates;
        std::vector<std::pair<EventListener*,InputActions> > globalEvents;
}g_InputManager;

#endif // INPUTMANAGER_H
