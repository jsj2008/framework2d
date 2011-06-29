#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

class Event;

class EventsListener /// FIXME rename EventListener
{
    public:
        EventsListener();
        virtual ~EventsListener();
        virtual bool trigger(Event* event)=0; /// Do I keep listening?
    protected:
    private:
};

#endif // EVENTLISTENER_H
