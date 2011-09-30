#ifndef EVENTTYPEREMOVER_H
#define EVENTTYPEREMOVER_H

#include <Events/EventListener.h>
class ScriptAction;

template <typename DerivedEvent>
class EventTypeRemover : public EventsListener<DerivedEvent> /// FIXME this is no longer generic, its specific to EventScripting and should be moved and renamed
{
    public:
        EventTypeRemover(ScriptAction* _action);
        virtual ~EventTypeRemover();
        bool trigger(DerivedEvent* _event);
    protected:
    private:
        ScriptAction* action;
};

#include <GameModes/Editor/DynamicEditor/EventScripter/ScriptAction.h>
template <typename DerivedEvent>
EventTypeRemover<DerivedEvent>::EventTypeRemover(ScriptAction* _action)
{
    //ctor
    action = _action;
}

template <typename DerivedEvent>
EventTypeRemover<DerivedEvent>::~EventTypeRemover()
{
    //dtor
}

template <typename DerivedEvent>
bool EventTypeRemover<DerivedEvent>::trigger(DerivedEvent* _event)
{
    action->trigger();
    return true;
}

#endif // EVENTTYPEREMOVER_H
