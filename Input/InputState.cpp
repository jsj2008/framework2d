#include "InputState.h"
#include <SDL/SDL_events.h>
#include <Input/EventListener.h>
#include <Input/Mouse/ClickEvent.h>
#include <Graphics/GraphicsManager.h>
InputState::InputState()
{
    //ctor
    controls = new ControlStruct[eInputActionsMax]{'w','a','s','d',SDLK_KP_PLUS,SDLK_KP_MINUS};
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
    controls[eLeft].key = (SDLKey)'a'; /// wtf? no idea why this is neccessary
    Uint8* keys = SDL_GetKeyState(NULL);
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
                g_GraphicsManager.resize(Vec2i(event.resize.w,event.resize.h));
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                //for (unsigned int i = 0; i < clickEvents.size(); i++)
                for (unsigned int i = clickEvents.size()-1; i != (unsigned int)-1; i--)
                {
                    if (clickEvents[i]->buttonDown(Vec2i(event.button.x,event.button.y),event.button.button))
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
                    activeEvent->mouseMove(Vec2i(event.motion.x,event.motion.y));
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                if (event.button.button == SDL_BUTTON_WHEELUP)
                {
                    keys[SDLK_KP_PLUS] = 1;
                }
                else if (event.button.button == SDL_BUTTON_WHEELDOWN)
                {
                    keys[SDLK_KP_MINUS] = 1;
                }
                else if (activeEvent != NULL)
                {
                    activeEvent->buttonUp(Vec2i(event.button.x,event.button.y),event.button.button);
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
    for (int i = 0; i < eInputActionsMax; i++)
    {
        if (keys[controls[i].key])
        {
            if (controls[i].event != NULL)
            {
                controls[i].event->trigger((InputActions)i);
            }
        }
    }
    keys[SDLK_KP_PLUS] = keys[SDLK_KP_MINUS] = 0;
    return returnValue;
}
void InputState::render()
{
    for (unsigned int i = 0; i < clickEvents.size(); i++)
    {
        clickEvents[i]->render();
    }
}
















