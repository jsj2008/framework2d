#ifndef JOINTEDITOR_H
#define JOINTEDITOR_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickNoEvent.h>
class EditorStateSwitcher;
class SelectionBox;
class b2Body;
class FreeCamera;
class EditorMode;
#define NUM_JOINT_MODES 1

class JointEditor : public GameMode, public ClickNoEvent
{
    public:
        JointEditor(FreeCamera* camera, EditorMode* _editorMode);
        void init();
        virtual ~JointEditor();
        void registerEvent(InputContext* event);
        bool activate(const CEGUI::EventArgs&);
    protected:
    private:
        bool v_Update(){return true;} // FIXME
        InputContext* modes[NUM_JOINT_MODES];
        EditorStateSwitcher* stateSwitcher;
        EditorMode* editorMode;
};

#endif // JOINTEDITOR_H
