#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../GameMode.h"
#include <Input/Mouse/ClickNoEvent.h>
class InputState;
class EditorStateSwitcher;

class EditorMode : public GameMode, public ClickNoEvent
{
    public:
        EditorMode();
        virtual ~EditorMode();
    protected:
    private:
        EditorStateSwitcher* selectionBox;
};

#endif // EDITORMODE_H
