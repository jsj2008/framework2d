#include "InputManager.h"
#include <SDL/SDL_events.h>

InputManager::InputManager()
{
    //ctor
    controls = new SDLKey[eActionsMax];
    controls[eUp] = (SDLKey)'w';
    controls[eDown] = (SDLKey)'a';
    controls[eLeft] = (SDLKey)'s';
    controls[eRight] = (SDLKey)'d';
}

InputManager::~InputManager()
{
    //dtor
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
                for (int i = 0; i < eActionsMax; i++)
                {
                    if (controls[i] == event.key.keysym.sym)
                    {
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
