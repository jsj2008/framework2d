#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event;
class EventsListener;

class EventHandler
{
    public:
        EventHandler()
        {
            listener = nullptr;
        }
        virtual ~EventHandler()
        {

        }
        void trigger(Event* event)
        {
            privateTrigger(event);
        }
        void registerListener(EventsListener* _listener)
        {
            privateRegisterListener(_listener);
        }
    protected:
    private:
        void privateTrigger(Event* event);
        void privateRegisterListener(EventsListener* _listener);
        EventsListener* listener;
};

#endif // EVENTHANDLER_H
