#ifndef DEATHSCRIPTEVENT_H
#define DEATHSCRIPTEVENT_H

#include <GameModes/Editor/EventScripter/ScriptEvent.h>
#include <Events/EventListener.h>
#include <Events/InstanceEvents/Events/DeathEvent.h>
#include <Events/Events/FactoryUsageEvent.h>
#include <string>
class ScriptAction;
template <typename DerivedEvent>
class InstanceEventListener;

template <typename Product>
class DeathScriptEvent : public ScriptEvent, public EventsListener<FactoryUsageEvent<Product>>
{
    public:
        DeathScriptEvent(const std::string& _name, InstanceEventListener<DeathEvent<Product>>* _listener);
        virtual ~DeathScriptEvent();
        bool trigger(FactoryUsageEvent<Product>* _event);
    protected:
    private:
        InstanceEventListener<DeathEvent<Product>>* listener;
};

template <typename Product>
DeathScriptEvent<Product>::DeathScriptEvent(const std::string& _name, InstanceEventListener<DeathEvent<Product>>* _listener)
{
    //ctor
    listener = _listener;
}

template <typename Product>
DeathScriptEvent<Product>::~DeathScriptEvent()
{
    //dtor
}

template <typename Product>
bool DeathScriptEvent<Product>::trigger(FactoryUsageEvent<Product>* _event)
{
    _event->get()->registerDeathListener(listener);
    return true;
}
#endif // DEATHSCRIPTEVENT_H
