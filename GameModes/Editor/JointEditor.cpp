#include "JointEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <GameModes/Editor/EditorStateSwitcher.h>
#include <GameModes/Editor/Joints/AllJointEditors.h>

JointEditor::JointEditor(FreeCamera* camera, EditorMode* _editorMode)
{
    //ctor
    mCamera = camera;
    editorMode = _editorMode;
}

void JointEditor::init()
{
    mCamera->activate();
    modes[0] = new DistanceJointEditor((FreeCamera*)mCamera, editorMode);
    stateSwitcher = new EditorStateSwitcher("JointEditor/TabControl",{"DistanceJoints"}, modes);

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
bool JointEditor::activate(const CEGUI::EventArgs&)
{
    stateSwitcher->eventShow();
    g_InputManager.setActiveEvent(this);
    return true;
}
