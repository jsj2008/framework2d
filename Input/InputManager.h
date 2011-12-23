#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <SDL/SDL_events.h>
#include <Types/Vec2i.h>
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

class InputContext;
class EventListener;
class InputGrabber;
class TextBox;
class ButtonPressEvent;
class ButtonReleaseEvent;
template <typename DerivedEvent>
class InstanceEventListener;
template <typename DerivedEvent>
class InstanceEventHandler;

struct InputManagerButtonStruct;
extern class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void cleanup();
        void changeResolution(const Vec2i newResolution);
        bool processInput();
        void registerStateSelect(InputContext* state, const char* name);
        void registerEvent(EventListener* event, InputActions action);
        void unregisterEvent(EventListener* event, InputActions action);
        void registerGlobalEvent(EventListener* event, InputActions action); /// These are global controls
        void render();
        void setActiveEvent(InputContext* _activeEvent);

        unsigned int registerButtonDownListener(const std::string& buttonName, InstanceEventListener<ButtonPressEvent>* _listener);
        unsigned int registerButtonUpListener(const std::string& buttonName, InstanceEventListener<ButtonReleaseEvent>* _listener);
        unsigned int registerButtonListener(const std::string& buttonName, InstanceEventListener<ButtonPressEvent>* _pressListener, InstanceEventListener<ButtonReleaseEvent>* _releaseListener);
    protected:
    private:
        struct ControlStruct
        {
            ControlStruct(SDLKey _key){key = _key;event = 0; pressed = false;}
            ControlStruct(char _key){key = SDLKey(_key);event = 0; pressed = false;}
            SDLKey key;
            EventListener* event;
            bool pressed;
        };
        ControlStruct* controls;
        InputContext* activeEvent;
        bool currentlyActive;
        InputGrabber* inputGrabber;
        Vec2i currentResolution;
        unsigned int* globalEventsSizeWhenSeen;
        std::vector<std::pair<EventListener*,InputActions> > globalEvents;

        typedef unsigned int SDLKeyTypeDef;
        std::vector<InputManagerButtonStruct*> buttonEvents;
        std::unordered_map<SDLKeyTypeDef, InputManagerButtonStruct*> buttonMap;
        std::unordered_map<std::string, std::pair<SDLKeyTypeDef, InputManagerButtonStruct*>> controlMap;
        InputManagerButtonStruct* getOrCreateButtonStruct(const std::string& _controlName);
}g_InputManager;

#endif // INPUTMANAGER_H
