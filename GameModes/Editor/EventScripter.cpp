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
    events->hide();
    actions->hide();
}

EventScripter::~EventScripter()
{
    //dtor
}

void EventScripter::init()
{
    CEGUI::TabControl* tabControl = static_cast<CEGUI::TabControl*>(CEGUI::System::getSingleton().getGUISheet()->getChildRecursive("Root/Frame/TabControl"));
    CEGUI::Window* root = tabControl->getTabContentsAtIndex(3); /// FIXME shit be bein stoopid
    root->subscribeEvent(CEGUI::Window::EventShown, {&EventScripter::show, this});
    root->subscribeEvent(CEGUI::Window::EventHidden, {&EventScripter::hide, this});
    scriptList = static_cast<CEGUI::Listbox*>(root->getChild("EventScripting/ScriptList"));
    root->getChild("EventScripting/CreateButton")->subscribeEvent(CEGUI::PushButton::EventClicked, {&EventScripter::createButton, this});
}

bool EventScripter::createButton(const CEGUI::EventArgs& _args)
{
    ScriptEvent* event = events->createScriptEvent(actions->createActionEvent());
    return true;
}
bool EventScripter::show(const CEGUI::EventArgs& _args)
{
    events->show();
    actions->show();
    return true;
}
bool EventScripter::hide(const CEGUI::EventArgs& _args)
{
    events->hide();
    actions->hide();
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
