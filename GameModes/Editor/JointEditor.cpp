#include "JointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <GameModes/Editor/EditorStateSwitcher.h>
#include <GameModes/Editor/Joints/AllJointEditors.h>

JointEditor::JointEditor(FreeCamera* camera)
{
    //ctor
    mCamera = camera;
}

void JointEditor::init()
{
    mCamera->activate();
    modes[0] = new DistanceJointEditor((FreeCamera*)mCamera);
    stateSwitcher = new EditorStateSwitcher("JointEditor/TabControl",{"DistanceJoints"}, modes);
    registerEvent(stateSwitcher);

    for (unsigned int i = 0; i < NUM_JOINT_MODES; i++)
    {
        modes[i]->init();
    }
}
JointEditor::~JointEditor()
{
    //dtor
    delete stateSwitcher;
}
void JointEditor::registerEvent(InputContext* event)
{
    for (unsigned int i = 0; i < NUM_JOINT_MODES; i++)
    {
        //modes[i]->registerEvent(event);
    }
}
bool JointEditor::activate(const CEGUI::EventArgs&)
{
    stateSwitcher->eventShow();
    return true;
}
