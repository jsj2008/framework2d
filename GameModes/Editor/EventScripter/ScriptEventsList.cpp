#include "ScriptEventsList.h"
#include <GameModes/Editor/EventScripter/Events/AllScriptEvents.h>
#include <Entities/Entity.h>
#include <Events/EventTypeRemover.h>
#include <Events/Events.h>
#include <CEGUI/CEGUI.h>

ScriptEventsList::ScriptEventsList()
{
    //ctor
    window = CEGUI::System::getSingleton().getGUISheet()->getChild("Root/Events");
    eventList = static_cast<CEGUI::Combobox*>(window->getChild("Root/Events/Combobox"));
}

ScriptEventsList::~ScriptEventsList()
{
    //dtor
}

ScriptEvent* ScriptEventsList::createScriptEvent(ScriptAction* _action)
{
    //return new DeathScriptEvent<Entity>("player", new EventTypeRemover<DeathEvent<Entity>>(_action));
    auto script = new StandardScriptEvent<FactoryUsageEvent<Entity>>(_action);
    Events::global().registerListener(script, {eBlockQueue});
    return script;
}

void ScriptEventsList::show()
{
    window->setVisible(true);
}
void ScriptEventsList::hide()
{
    window->setVisible(false);
}
