#ifndef EditorStateSwitcher_H
#define EditorStateSwitcher_H

#include <Input/Mouse/SelectionBox.h>
class GameMode;

class EditorStateSwitcher : public SelectionBox
{
    public:
        EditorStateSwitcher(const Rect& _Rect, std::initializer_list<const char*> icons, GameMode* _root, GameMode** _states);
        virtual ~EditorStateSwitcher();
    protected:
    private:
        void selectionTrigger();
        GameMode** states;
        GameMode* root;
};

#endif // EditorStateSwitcher_H
