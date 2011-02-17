#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../GameMode.h"
class InputState;

class EditorMode : public GameMode
{
    public:
        EditorMode();
        virtual ~EditorMode();
    protected:
    private:
        InputState* geometryEditor;
};

#endif // EDITORMODE_H
