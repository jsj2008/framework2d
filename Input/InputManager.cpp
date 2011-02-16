#include "InputManager.h"
#include <SDL/SDL_events.h>
#include <Input/EventListener.h>
InputManager g_InputManager;
InputManager::InputManager()
{
    //ctor
    controls = new ControlStruct[eInputActionsMax]{'w','a','s','d'};
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::registerEvent(EventListener* event, InputActions action)
{
    controls[action].event = event;
}
bool InputManager::processInput()
{
    bool returnValue = true;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                for (int i = 0; i < eInputActionsMax; i++)
                {
                    if (controls[i].key == event.key.keysym.sym)
                    {
                        controls[i].event->trigger(i);
                    }
                }
                break;
            }
            case SDL_QUIT:
            {
                returnValue = false;
                break;
            }
        }
    }
    return returnValue;
}
