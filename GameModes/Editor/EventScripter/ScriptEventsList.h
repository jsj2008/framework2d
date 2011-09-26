#ifndef SCRIPTEVENTSLIST_H
#define SCRIPTEVENTSLIST_H

namespace CEGUI
{
    class Window;
}
class ScriptEvent;

class ScriptEventsList
{
    public:
        ScriptEventsList();
        virtual ~ScriptEventsList();
        ScriptEvent* createScriptEvent();
    protected:
    private:
        CEGUI::Window* window;
};

#endif // SCRIPTEVENTSLIST_H
