#include "JointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <Input/Mouse/SelectionBox.h>
#include <Input/Mouse/SliderBar.h>
#include <Input/Mouse/CheckBox.h>
#include <GameModes/Editor/EditorStateSwitcher.h>
#include <GameModes/Editor/Joints/AllJointEditors.h>

JointEditor::JointEditor(FreeCamera* camera, const Rect& _Rect)
{
    //ctor
    mCamera = camera;
    mInputState = new InputState;
    camera->registerWithInputState(mInputState);
    Rect stateSwitcherRect(0,100,500,200);
    CheckBox* collide = new CheckBox(Vec2i(0,200),"Collide");
    modes[0] = new DistanceJointEditor(camera,collide);
    stateSwitcher = new EditorStateSwitcher(stateSwitcherRect,{"Distance"}, this, modes);
    registerEvent(stateSwitcher);
    mInputState->registerEvent(collide);
}

JointEditor::~JointEditor()
{
    //dtor
    delete stateSwitcher;
}
void JointEditor::registerEvent(ClickEvent* event)
{
    mInputState->registerEvent(event);
    for (unsigned int i = 0; i < NUM_JOINT_MODES; i++)
    {
        modes[i]->registerEvent(event);
    }
}
