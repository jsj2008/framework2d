#ifndef EditorStateSwitcher_H
#define EditorStateSwitcher_H

#include <initializer_list>
#include <vector>
#include <Input/Mouse/ClickNoEvent.h>
class GameMode;
class InputContext;
namespace CEGUI
{
    class TabControl;
}

class EditorStateSwitcher : public ClickNoEvent
{
    public:
        EditorStateSwitcher(const char* tabControlName, std::initializer_list<const char*> icons, InputContext** _states);
        virtual ~EditorStateSwitcher();
        void push(const char* name, InputContext* event);
        void eventShow();
    protected:
    private:
        void selectionTrigger();
        std::vector<InputContext*> states;
        CEGUI::TabControl* tab;
};

#endif // EditorStateSwitcher_H
