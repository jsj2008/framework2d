#ifndef EVENTSLISTENER_H
#define EVENTSLISTENER_H

class Event;

template <typename EventType>
class EventsListener /// FIXME rename EventListener
{
    public:
        EventsListener();
        virtual ~EventsListener();
        virtual bool trigger(EventType* event)=0; /// Do I keep listening?
    protected:
    private:
};


template <typename EventType>
EventsListener<EventType>::EventsListener()
{
    //ctor
}

template <typename EventType>
EventsListener<EventType>::~EventsListener()
{
    //dtor
}

#endif // EVENTLISTENER_H
