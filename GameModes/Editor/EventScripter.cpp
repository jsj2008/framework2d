#include "EventScripter.h"
#include <Graphics/Camera/FreeCamera.h>
#include <GameModes/Editor/EventScripter/ScriptEventsList.h>
#include <GameModes/Editor/EventScripter/ActionEventsList.h>

EventScripter::EventScripter(FreeCamera* _camera, EditorMode* _editorMode)
{
    //ctor
    _camera->activate();
    mCamera = _camera;
    editorMode = _editorMode;
    events = new ScriptEventsList;
    actions = new ActionEventsList;
}

EventScripter::~EventScripter()
{
    //dtor
}

void EventScripter::init()
{
    CEGUI::TabControl* tabControl = static_cast<CEGUI::TabControl*>(CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("Root/Frame/TabControl"));
    CEGUI::Window* root = tabControl->getTabContentsAtIndex(3); /// FIXME shit be bein stoopid
    scriptList = static_cast<CEGUI::Listbox*>(root->getChild("EventScripting/ScriptList"));
    root->getChild("EventScripting/CreateButton")->subscribeEvent(CEGUI::PushButton::EventClicked, {&EventScripter::createButton, this});
}

bool EventScripter::createButton(const CEGUI::EventArgs& _args)
{
    ScriptEvent* event = events->createScriptEvent();
    ScriptAction* action = actions->createActionEvent();
    EventScript* script = new EventScript(event, action);
    return true;
}
bool EventScripter::update()
{
    return true;
}
void EventScripter::buttonDown(Vec2i mouse, unsigned char button)
{

}
void EventScripter::mouseMove(Vec2i mouse)
{

}
void EventScripter::buttonUp(Vec2i mouse, unsigned char button)
{

}
