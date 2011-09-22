#ifndef EVENTS_H
#define EVENTS_H

#include <Events/GenericEvent.h>
#include <Events/EventHandler.h>
class Event;
template <typename DerivedEvent>
class EventsListener;

class Events
{
    public:
        static Events& global(); /// Not a singleton by design

        template <typename DerivedEvent>
        void triggerEvent(DerivedEvent* event);

        template <typename DerivedEvent>
        void registerListener(EventsListener<DerivedEvent>* listener, EventListenerProperties _properties);

        template <typename DerivedEvent>
        void unregisterListener(EventsListener<DerivedEvent>* listener, bool _blockingQueue);

        template <GenericEvents eventName>
        void triggerGenericEvent();
    protected:
    private:
        Events();
        virtual ~Events();

        template <typename DerivedEvent>
        EventHandler<DerivedEvent>& getHandler();
};

/**
* Implementation
*/

#include <Events/EventListener.h>

template <typename DerivedEvent>
void Events::triggerEvent(DerivedEvent* event)
{
    getHandler<DerivedEvent>().trigger(event);
}

template <typename DerivedEvent>
void Events::registerListener(EventsListener<DerivedEvent>* listener, EventListenerProperties _properties)
{
    getHandler<DerivedEvent>().registerListener(listener, _properties);
}

template <typename DerivedEvent>
void Events::unregisterListener(EventsListener<DerivedEvent>* listener, bool _blockingQueue)
{
    getHandler<DerivedEvent>().unregisterListener(listener, _blockingQueue);
}


template <typename DerivedEvent>
EventHandler<DerivedEvent>& Events::getHandler()
{
    static EventHandler<DerivedEvent> handler;
    return handler;
}
#endif // EVENTS_H
