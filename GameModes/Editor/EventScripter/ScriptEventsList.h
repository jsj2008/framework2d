#ifndef SCRIPTEVENTSLIST_H
#define SCRIPTEVENTSLIST_H

namespace CEGUI
{
    class Window;
    class Combobox;
}
class ScriptEvent;
class ScriptEventFactory;
class ScriptAction;

class ScriptEventsList
{
    public:
        ScriptEventsList();
        virtual ~ScriptEventsList();
        ScriptEvent* createScriptEvent(ScriptAction* _action);
        void show();
        void hide();
    protected:
    private:
        CEGUI::Window* window;
        CEGUI::Combobox* eventList;
};

#endif // SCRIPTEVENTSLIST_H
