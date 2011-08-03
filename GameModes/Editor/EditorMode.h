#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../GameMode.h"
#include <Input/Mouse/ClickNoEvent.h>
class InputState;
class EditorStateSwitcher;
class Level;
class PhysicsManager;

class EditorMode : public GameMode, public ClickNoEvent
{
    public:
        EditorMode(Level* _editing, InputContext* _playMode); /// FIXME change this to be mutable and managed internally
        virtual ~EditorMode();
        PhysicsManager* getActiveWorld();
        Level* getActiveLevel();
    protected:
    private:
        EditorStateSwitcher* selectionBox;
        Level* editing;
};

#endif // EDITORMODE_H
