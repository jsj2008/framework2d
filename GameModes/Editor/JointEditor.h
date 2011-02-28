#ifndef JOINTEDITOR_H
#define JOINTEDITOR_H

#include <GameModes/GameMode.h>
#include <Input/Mouse/ClickReleaseEvent.h>
class EditorStateSwitcher;
class SelectionBox;
class b2Body;
class FreeCamera;
#define NUM_JOINT_MODES 1

class JointEditor : public GameMode
{
    public:
        JointEditor(FreeCamera* camera, const Rect& _Rect);
        virtual ~JointEditor();
        void registerEvent(ClickEvent* event);
    protected:
    private:
        GameMode* modes[NUM_JOINT_MODES];
        EditorStateSwitcher* stateSwitcher;
};

#endif // JOINTEDITOR_H
