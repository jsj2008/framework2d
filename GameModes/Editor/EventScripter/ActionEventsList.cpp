#include "ActionEventsList.h"
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
