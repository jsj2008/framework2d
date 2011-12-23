#include "ActionEventsList.h"
#include <GameModes/Editor/EventScripter/Actions/AllScriptActions.h>
#include <CEGUI/CEGUI.h>

ActionEventsList::ActionEventsList()
{
    //ctor
    window = CEGUI::System::getSingleton().getGUISheet()->getChild("Root/Actions");
}

ActionEventsList::~ActionEventsList()
{
    //dtor
}

void ActionEventsList::show()
{
    window->setVisible(true);
}
void ActionEventsList::hide()
{
    window->setVisible(false);
}

ScriptAction* ActionEventsList::createActionEvent()
{
    return new LogScriptAction("This is a log of some description");
}
