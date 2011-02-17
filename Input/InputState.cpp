#include "InputState.h"
#include <SDL/SDL_events.h>
#include <Input/EventListener.h>
#include <Input/Mouse/ClickEvent.h>
#include <Graphics/GraphicsManager.h>
InputState::InputState()
{
    //ctor
    controls = new ControlStruct[eInputActionsMax]{'w','a','s','d'};
    activeEvent = NULL;
}

InputState::~InputState()
{
    //dtor
}

void InputState::registerEvent(EventListener* event, InputActions action)
{
    controls[action].event = event;
}
void InputState::registerEvent(ClickEvent* event)
{
    clickEvents.push_back(event);
}
bool InputState::processInput()
{
    controls[eLeft].key = 'a'; /// wtf? no idea why this is neccessary
    bool returnValue = true;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            /*case SDL_KEYDOWN:
            {
                for (int i = 0; i < eInputActionsMax; i++)
                {
                    if (controls[i].key == event.key.keysym.sym)
                    {
                        if (controls[i].event != NULL)
                        {
                            controls[i].event->trigger(InputActions(i));
                        }
                    }
                }
                break;
            }*/
            case SDL_VIDEORESIZE:
            {
                g_GraphicsManager.resize(event.resize.w,event.resize.h);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                for (unsigned int i = 0; i < clickEvents.size(); i++)
                {
                    if (clickEvents[i]->buttonDown(event.button.x,event.button.y))
                    {
                        activeEvent = clickEvents[i];
                        break;
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                if (activeEvent != NULL)
                {
                    activeEvent->mouseMove(event.motion.x,event.motion.y);
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                if (activeEvent != NULL)
                {
                    activeEvent->buttonUp(event.button.x,event.button.y);
                    activeEvent = NULL;
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
    Uint8* keys = SDL_GetKeyState(NULL);
    for (int i = 0; i < eInputActionsMax; i++)
    {
        if (keys[controls[i].key])
        {
            controls[i].event->trigger((InputActions)i);
        }
    }
    return returnValue;
}

















