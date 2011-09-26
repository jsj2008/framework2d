#include "ScriptEventsList.h"
#include <CEGUI/CEGUI.h>

ScriptEventsList::ScriptEventsList()
{
    //ctor
    window = CEGUI::System::getSingleton().getGUISheet()->getChild("Root/Events");
}

ScriptEventsList::~ScriptEventsList()
{
    //dtor
}
