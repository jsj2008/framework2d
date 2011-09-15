#ifndef EVENTSLISTENER_H
#define EVENTSLISTENER_H

template <typename EventType>
class EventHandler;

template <typename EventType>
class EventsListener /// FIXME rename EventListener
{
    public:
        EventsListener();
        virtual ~EventsListener();
        virtual bool trigger(EventType* event)=0; /// Do I keep listening?
    protected:
    private:
        friend class EventHandler<EventType>;
        EventsListener<EventType>* prev,* next;

};


template <typename EventType>
EventsListener<EventType>::EventsListener()
{
    //ctor
    prev = next = nullptr;
}

template <typename EventType>
EventsListener<EventType>::~EventsListener()
{
    //dtor
}

#endif // EVENTLISTENER_H
