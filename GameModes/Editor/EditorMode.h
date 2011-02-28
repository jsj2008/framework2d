#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../GameMode.h"
class InputState;
class SelectionBox;

class EditorMode : public GameMode
{
    public:
        EditorMode();
        virtual ~EditorMode();
    protected:
    private:
        SelectionBox* selectionBox;
};

#endif // EDITORMODE_H
