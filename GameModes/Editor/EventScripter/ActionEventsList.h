#ifndef ACTIONEVENTSLIST_H
#define ACTIONEVENTSLIST_H

namespace CEGUI
{
    class Window;
}
class ScriptAction;

class ActionEventsList /// FIXME rename this ScriptActionsList
{
    public:
        ActionEventsList();
        virtual ~ActionEventsList();
        ScriptAction* createActionEvent();
    protected:
    private:
        CEGUI::Window* window;
};

#endif // ACTIONEVENTSLIST_H
