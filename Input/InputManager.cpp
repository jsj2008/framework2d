#include "InputManager.h"
#include <Graphics/GraphicsManager.h>
#include <Input/EventListener.h>
#include <Input/Mouse/InputContext.h>
#include <CEGUI/CEGUI.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_timer.h>
InputManager g_InputManager;
using namespace std;
InputManager::InputManager()
{
    //ctor
    activeEvent = nullptr;
    inputGrabber = nullptr;
    controls = new ControlStruct[eInputActionsMax]{'w','a','s','d',SDLK_KP_PLUS,SDLK_KP_MINUS};
    currentlyActive = false;
}

InputManager::~InputManager()
{
    //dtor
}
void InputManager::changeResolution(const Vec2i newResolution)
{
}
void InputManager::registerEvent(EventListener* event, InputActions action)
{
    controls[action].event = event;
}
void InputManager::registerGlobalEvent(EventListener* event, InputActions action)
{
}
void InputManager::render()
{
    activeEvent->render();
}
void InputManager::setActiveEvent(InputContext* _activeEvent)
{
    activeEvent = _activeEvent;
}
void handle_mouse_down(Uint8 button);
void handle_mouse_down(Uint8 button)
{
switch ( button )
    {
    // handle real mouse buttons
    case SDL_BUTTON_LEFT:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
        break;
    case SDL_BUTTON_MIDDLE:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
        break;
    case SDL_BUTTON_RIGHT:
        CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
        break;

    // handle the mouse wheel
    case SDL_BUTTON_WHEELDOWN:
        CEGUI::System::getSingleton().injectMouseWheelChange( -1 );
        break;
    case SDL_BUTTON_WHEELUP:
        CEGUI::System::getSingleton().injectMouseWheelChange( +1 );
        break;
    }
}
void handle_mouse_up(Uint8 button);
void handle_mouse_up(Uint8 button)
	{
	switch ( button )
		{
		case SDL_BUTTON_LEFT:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
			break;
		case SDL_BUTTON_MIDDLE:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
			break;
		case SDL_BUTTON_RIGHT:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
			break;
		}
	}
bool InputManager::processInput()
{
    controls[eLeft].key = (SDLKey)'a'; /// wtf? no idea why this is neccessary
    Uint8* keys = SDL_GetKeyState(nullptr);
    bool returnValue = true;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                /*for (int i = 0; i < eInputActionsMax; i++)
                {
                    if (controls[i].key == event.key.keysym.sym)
                    {
                        if (controls[i].event != nullptr)
                        {
                            controls[i].event->trigger(InputActions(i));
                        }
                    }
                }*/
                CEGUI::System::getSingleton().injectKeyDown(event.key.keysym.scancode);
                if (event.key.keysym.unicode != 0)
                {
                    CEGUI::System::getSingleton().injectChar(event.key.keysym.unicode);
                }
                else
                {
                    CEGUI::System::getSingleton().injectChar(event.key.keysym.sym);
                }
                break;
            }
            case SDL_VIDEORESIZE:
            {
                g_GraphicsManager.resize(Vec2i(event.resize.w,event.resize.h));
                g_InputManager.changeResolution(Vec2i(event.resize.w,event.resize.h));
                CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size(event.resize.w,event.resize.h));
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                //for (unsigned int i = 0; i < clickEvents.size(); i++)
                 handle_mouse_down(event.button.button);
                CEGUI::Point mousePoint(event.button.x,event.button.y);
                CEGUI::Window* hitChild = CEGUI::System::getSingleton().getGUISheet()->getChildAtPosition(mousePoint);
                bool isHit;
                if(hitChild)
                    isHit = hitChild->isHit(mousePoint);
                else
                    isHit = false;
                if (activeEvent != nullptr && !isHit)
                {
                    activeEvent->buttonDown(Vec2i(event.button.x,event.button.y),event.button.button);
                    currentlyActive = true;
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                CEGUI::System::getSingleton().injectMousePosition(
                                  static_cast<float>(event.motion.x),
                                  static_cast<float>(event.motion.y));

                if (activeEvent != nullptr && currentlyActive)
                {
                    activeEvent->mouseMove(Vec2i(event.motion.x,event.motion.y));
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                handle_mouse_up(event.button.button);
                if (event.button.button == SDL_BUTTON_WHEELUP)
                {
                    keys[SDLK_KP_PLUS] = 1;
                }
                else if (event.button.button == SDL_BUTTON_WHEELDOWN)
                {
                    keys[SDLK_KP_MINUS] = 1;
                }
                if (activeEvent != nullptr && currentlyActive)
                {
                    activeEvent->buttonUp(Vec2i(event.button.x,event.button.y),event.button.button);
                    currentlyActive = false;
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
    for (unsigned int i = 0; i < eInputActionsMax; i++)
    {
        if (controls[i].event != nullptr)
        {
            controls[i].event->resetInput();
        }
    }
    for (int i = 0; i < eInputActionsMax; i++)
    {
        if (keys[controls[i].key])
        {
            if (controls[i].event != nullptr)
            {
                controls[i].event->trigger((InputActions)i);
            }
        }
    }
    keys[SDLK_KP_PLUS] = keys[SDLK_KP_MINUS] = 0;
    return returnValue;
}
































