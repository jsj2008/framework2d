#ifndef EVENTS_H
#define EVENTS_H

class Event;
template <typename DerivedEvent>
class EventsListener;
class EventHandler;

class Events
{
    public:
        static Events& global(); /// Not a singleton by design

        template <typename DerivedEvent>
        void triggerEvent(DerivedEvent* event);

        template <typename DerivedEvent>
        void registerListener(EventsListener<DerivedEvent>* listener);

        template <typename DerivedEvent>
        void unregisterListener(EventsListener<DerivedEvent>* listener);
    protected:
    private:
        Events();
        virtual ~Events();

        template <typename DerivedEvent>
        EventsListener<DerivedEvent>** getListener();
};

/**
* Implementation
*/

#include <Events/EventListener.h>

template <typename DerivedEvent>
void Events::triggerEvent(DerivedEvent* event)
{
    if ((*getListener<DerivedEvent>()) != nullptr)
        (*getListener<DerivedEvent>())->trigger(event);
}

template <typename DerivedEvent>
void Events::registerListener(EventsListener<DerivedEvent>* listener)
{
    *getListener<DerivedEvent>() = listener;
}

template <typename DerivedEvent>
void Events::unregisterListener(EventsListener<DerivedEvent>* listener)
{
    *getListener<DerivedEvent>() = nullptr;
}


template <typename DerivedEvent>
EventsListener<DerivedEvent>** Events::getListener()
{
    static EventsListener<DerivedEvent>* listener = nullptr;
    return &listener;
}
#endif // EVENTS_H
