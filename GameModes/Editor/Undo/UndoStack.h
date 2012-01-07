#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <vector>
#include <CEGUI/CEGUI.h>
class UndoEntry;
class UndoResources;
class UndoStack
{
    public:
        UndoStack();
        virtual ~UndoStack();
        void init();
        static UndoStack& global(); /// Not necessarily singleton by design
        void addEntry(UndoEntry* _entry);
        bool undoButton(const CEGUI::EventArgs& _args);
        bool redoButton(const CEGUI::EventArgs& _args);
    protected:
    private:
        void setInfoboxText();
        CEGUI::Window* window;
        CEGUI::Listbox* listBox;
        std::vector<UndoEntry*> undoStack;
        unsigned int stackOffset; /// Number of entries have been 'redone'
};

#endif // UNDOSTACK_H
