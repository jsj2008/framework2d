#ifndef EVENTSCRIPTER_H
#define EVENTSCRIPTER_H

#include <Input/Mouse/InputContext.h>
#include <GameModes/GameMode.h>
class FreeCamera;
class EditorMode;
class ScriptEventsList;
class ActionEventsList;
class EventType;
class ActionType;
class EventScript;
namespace CEGUI
{
    class Window;
    class Listbox;
    class EventArgs;
}

class EventScripter : public GameMode, public InputContext
{
    public:
        EventScripter(FreeCamera* _camera, EditorMode* _editorMode);
        virtual ~EventScripter();
        void init();
        bool update();
        void buttonDown(Vec2i mouse, unsigned char button);
        void mouseMove(Vec2i mouse);
        void buttonUp(Vec2i mouse, unsigned char button);
        void addEventType(EventType* _eventType);
        void addActionType(ActionType* _actionType);
        bool createButton(const CEGUI::EventArgs& _args);
    protected:
    private:
        EditorMode* editorMode;
        ScriptEventsList* events;
        ActionEventsList* actions;
        CEGUI::Listbox* scriptList;
};

#endif // EVENTSCRIPTER_H
