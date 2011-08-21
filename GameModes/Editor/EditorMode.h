#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../GameMode.h"
#include <Input/Mouse/ClickNoEvent.h>
class InputState;
class EditorStateSwitcher;
class Level;
class PhysicsManager;
class PlayMode;

class EditorMode : public GameMode, public ClickNoEvent
{
    public:
        EditorMode(PlayMode* _playMode); /// FIXME change this to be mutable and managed internally
        virtual ~EditorMode();
        PhysicsManager* getActiveWorld();
        Level* getActiveLevel();
        bool update();
    protected:
    private:
        EditorStateSwitcher* selectionBox;
        PlayMode* activeLevel;
};

#endif // EDITORMODE_H
