#include "InputManager.h"
#include <Graphics/GraphicsManager.h>
#include <Input/EventListener.h>
#include <Input/Mouse/InputContext.h>
#include <Events/InstanceEvents/InstanceEventHandler.h>
#include <Events/Events/ButtonPressEvent.h>
#include <Events/Events/ButtonReleaseEvent.h>
#include <Log/Log.h>
#include <CEGUI/CEGUI.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_timer.h>

struct InputManagerButtonStruct
{
    InstanceEventHandler<ButtonPressEvent> press;
    InstanceEventHandler<ButtonReleaseEvent> release;
    unsigned int buttonId;
};

InputManager g_InputManager;
using namespace std;

InputManager::InputManager()
:controlMap({
    {"Left", {'a', nullptr}},
    {"Right", {'d', nullptr}},
    {"Up", {'w', nullptr}},
})
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
unsigned int InputManager::registerButtonListener(const std::string& buttonName, InstanceEventListener<ButtonPressEvent>* _pressListener, InstanceEventListener<ButtonReleaseEvent>* _releaseListener)
{
    InputManagerButtonStruct* buttonStruct = getOrCreateButtonStruct(buttonName);
    buttonStruct->press.registerListener(_pressListener);
    buttonStruct->release.registerListener(_releaseListener);
    return buttonStruct->buttonId;
}
unsigned int InputManager::registerButtonDownListener(const std::string& buttonName, InstanceEventListener<ButtonPressEvent>* _listener)
{
    InputManagerButtonStruct* buttonStruct = getOrCreateButtonStruct(buttonName);
    buttonStruct->press.registerListener(_listener);
    return buttonStruct->buttonId;
}
unsigned int InputManager::registerButtonUpListener(const std::string& buttonName, InstanceEventListener<ButtonReleaseEvent>* _listener)
{
    InputManagerButtonStruct* buttonStruct = getOrCreateButtonStruct(buttonName);
    buttonStruct->release.registerListener(_listener);
    return buttonStruct->buttonId;
}
InputManagerButtonStruct* InputManager::getOrCreateButtonStruct(const std::string& _controlName)
{
    auto iter = controlMap.find(_controlName);
    if (iter == controlMap.end())
    {
        g_Log.error(std::string("No such control: ") + _controlName);
        return nullptr;
    }
    else
    {
        if (iter->second.second == nullptr)
        {
            InputManagerButtonStruct* newStruct = new InputManagerButtonStruct;
            newStruct->buttonId = buttonEvents.size();
            buttonEvents.push_back(newStruct);
            buttonMap[iter->second.first] = newStruct;
            iter->second.second = newStruct;
            return newStruct;
        }
        else return iter->second.second;
    }
}
void InputManager::changeResolution(const Vec2i newResolution)
{
}
void InputManager::registerEvent(EventListener* event, InputActions action)
{
    controls[action].event = event;
}
void InputManager::unregisterEvent(EventListener* event, InputActions action)
{
    if (controls[action].event == event)
        controls[action].event = nullptr;
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
    if (activeEvent != nullptr)
        activeEvent->deactivate();
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
CEGUI::uint SDLKeyToCEGUIKey(SDLKey key);
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
                InputManagerButtonStruct* buttons = buttonMap[event.key.keysym.sym];
                if (buttons != nullptr)
                {
                    ButtonPressEvent event(buttons->buttonId);
                    buttons->press.trigger(&event);
                }
                CEGUI::uint kc = SDLKeyToCEGUIKey(event.key.keysym.sym);

                CEGUI::System::getSingleton().injectKeyDown(kc);
                CEGUI::System::getSingleton().injectChar(event.key.keysym.unicode);
                //CEGUI::System::getSingleton().injectChar(kc);

                break;
            }
            case SDL_KEYUP:
            {
                InputManagerButtonStruct* buttons = buttonMap[event.key.keysym.sym];
                if (buttons != nullptr)
                {
                    ButtonReleaseEvent event(buttons->buttonId);
                    buttons->release.trigger(&event);
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
    CEGUI::System::getSingleton().injectTimePulse(1.0f/60.0f);
    for (unsigned int i = 0; i < eInputActionsMax; i++)
    {
        if (controls[i].event != nullptr)
        {
            //controls[i].event->trigger(eResetInput);
        }
    }
    for (int i = 0; i < eInputActionsMax; i++)
    {
        bool pressed = keys[controls[i].key];
        if (pressed != controls[i].pressed)
        {
            controls[i].pressed = pressed;
            if (controls[i].event != nullptr)
            {
                controls[i].event->trigger((InputActions)i, pressed);
            }
        }
    }
    keys[SDLK_KP_PLUS] = keys[SDLK_KP_MINUS] = 0;
    return returnValue;
}
CEGUI::uint SDLKeyToCEGUIKey(SDLKey key)
 {
     using namespace CEGUI;
     switch (key)
     {
     case SDLK_BACKSPACE:    return Key::Backspace;
     case SDLK_TAB:          return Key::Tab;
     case SDLK_RETURN:       return Key::Return;
     case SDLK_PAUSE:        return Key::Pause;
     case SDLK_ESCAPE:       return Key::Escape;
     case SDLK_SPACE:        return Key::Space;
     case SDLK_COMMA:        return Key::Comma;
     case SDLK_MINUS:        return Key::Minus;
     case SDLK_PERIOD:       return Key::Period;
     case SDLK_SLASH:        return Key::Slash;
     case SDLK_0:            return Key::Zero;
     case SDLK_1:            return Key::One;
     case SDLK_2:            return Key::Two;
     case SDLK_3:            return Key::Three;
     case SDLK_4:            return Key::Four;
     case SDLK_5:            return Key::Five;
     case SDLK_6:            return Key::Six;
     case SDLK_7:            return Key::Seven;
     case SDLK_8:            return Key::Eight;
     case SDLK_9:            return Key::Nine;
     case SDLK_COLON:        return Key::Colon;
     case SDLK_SEMICOLON:    return Key::Semicolon;
     case SDLK_EQUALS:       return Key::Equals;
     case SDLK_LEFTBRACKET:  return Key::LeftBracket;
     case SDLK_BACKSLASH:    return Key::Backslash;
     case SDLK_RIGHTBRACKET: return Key::RightBracket;
     case SDLK_a:            return Key::A;
     case SDLK_b:            return Key::B;
     case SDLK_c:            return Key::C;
     case SDLK_d:            return Key::D;
     case SDLK_e:            return Key::E;
     case SDLK_f:            return Key::F;
     case SDLK_g:            return Key::G;
     case SDLK_h:            return Key::H;
     case SDLK_i:            return Key::I;
     case SDLK_j:            return Key::J;
     case SDLK_k:            return Key::K;
     case SDLK_l:            return Key::L;
     case SDLK_m:            return Key::M;
     case SDLK_n:            return Key::N;
     case SDLK_o:            return Key::O;
     case SDLK_p:            return Key::P;
     case SDLK_q:            return Key::Q;
     case SDLK_r:            return Key::R;
     case SDLK_s:            return Key::S;
     case SDLK_t:            return Key::T;
     case SDLK_u:            return Key::U;
     case SDLK_v:            return Key::V;
     case SDLK_w:            return Key::W;
     case SDLK_x:            return Key::X;
     case SDLK_y:            return Key::Y;
     case SDLK_z:            return Key::Z;
     case SDLK_DELETE:       return Key::Delete;
     case SDLK_KP0:          return Key::Numpad0;
     case SDLK_KP1:          return Key::Numpad1;
     case SDLK_KP2:          return Key::Numpad2;
     case SDLK_KP3:          return Key::Numpad3;
     case SDLK_KP4:          return Key::Numpad4;
     case SDLK_KP5:          return Key::Numpad5;
     case SDLK_KP6:          return Key::Numpad6;
     case SDLK_KP7:          return Key::Numpad7;
     case SDLK_KP8:          return Key::Numpad8;
     case SDLK_KP9:          return Key::Numpad9;
     case SDLK_KP_PERIOD:    return Key::Decimal;
     case SDLK_KP_DIVIDE:    return Key::Divide;
     case SDLK_KP_MULTIPLY:  return Key::Multiply;
     case SDLK_KP_MINUS:     return Key::Subtract;
     case SDLK_KP_PLUS:      return Key::Add;
     case SDLK_KP_ENTER:     return Key::NumpadEnter;
     case SDLK_KP_EQUALS:    return Key::NumpadEquals;
     case SDLK_UP:           return Key::ArrowUp;
     case SDLK_DOWN:         return Key::ArrowDown;
     case SDLK_RIGHT:        return Key::ArrowRight;
     case SDLK_LEFT:         return Key::ArrowLeft;
     case SDLK_INSERT:       return Key::Insert;
     case SDLK_HOME:         return Key::Home;
     case SDLK_END:          return Key::End;
     case SDLK_PAGEUP:       return Key::PageUp;
     case SDLK_PAGEDOWN:     return Key::PageDown;
     case SDLK_F1:           return Key::F1;
     case SDLK_F2:           return Key::F2;
     case SDLK_F3:           return Key::F3;
     case SDLK_F4:           return Key::F4;
     case SDLK_F5:           return Key::F5;
     case SDLK_F6:           return Key::F6;
     case SDLK_F7:           return Key::F7;
     case SDLK_F8:           return Key::F8;
     case SDLK_F9:           return Key::F9;
     case SDLK_F10:          return Key::F10;
     case SDLK_F11:          return Key::F11;
     case SDLK_F12:          return Key::F12;
     case SDLK_F13:          return Key::F13;
     case SDLK_F14:          return Key::F14;
     case SDLK_F15:          return Key::F15;
     case SDLK_NUMLOCK:      return Key::NumLock;
     case SDLK_SCROLLOCK:    return Key::ScrollLock;
     case SDLK_RSHIFT:       return Key::RightShift;
     case SDLK_LSHIFT:       return Key::LeftShift;
     case SDLK_RCTRL:        return Key::RightControl;
     case SDLK_LCTRL:        return Key::LeftControl;
     case SDLK_RALT:         return Key::RightAlt;
     case SDLK_LALT:         return Key::LeftAlt;
     case SDLK_LSUPER:       return Key::LeftWindows;
     case SDLK_RSUPER:       return Key::RightWindows;
     case SDLK_SYSREQ:       return Key::SysRq;
     case SDLK_MENU:         return Key::AppMenu;
     case SDLK_POWER:        return Key::Power;
     default:                return 0;
     }
     return 0;
 }































