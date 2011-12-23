#ifndef STANDARDSCRIPTEVENT_H
#define STANDARDSCRIPTEVENT_H

#include <GameModes/Editor/EventScripter/ScriptEvent.h>
#include <Events/EventListener.h>
class ScriptAction;

template <typename DerivedEvent>
class StandardScriptEvent : public ScriptEvent, public EventsListener<DerivedEvent>
{
    public:
        StandardScriptEvent(ScriptAction* _action);
        virtual ~StandardScriptEvent();
        bool trigger(DerivedEvent* _event);
    protected:
    private:
        ScriptAction* action;
};

#include <GameModes/Editor/DynamicEditor/EventScripter/ScriptAction.h>

template <typename DerivedEvent>
StandardScriptEvent<DerivedEvent>::StandardScriptEvent(ScriptAction* _action)
{
    //ctor
    action = _action;
}

template <typename DerivedEvent>
StandardScriptEvent<DerivedEvent>::~StandardScriptEvent()
{
    //dtor
}

template <typename DerivedEvent>
bool StandardScriptEvent<DerivedEvent>::trigger(DerivedEvent* _event)
{
    action->trigger();
    return true;
}

#endif // STANDARDSCRIPTEVENT_H
