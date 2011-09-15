#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>
template <typename DerivedEvent>
class EventsListener;

enum EventListenerPropertiesEnum
{
    eReadQueue = 1 << 0,
    eClearQueue = 1 << 1,
    eBlockQueue = 1 << 2,
    eListenerPropertiesMax
};
struct EventListenerProperties
{
    EventListenerProperties(unsigned char _flags = eBlockQueue)
    {
        flags = _flags;
    }
    unsigned char flags;
    bool getFlag(EventListenerPropertiesEnum _flags)
    {
        return flags & _flags;
    }
};

template <typename DerivedEvent>
class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();
        void trigger(DerivedEvent* _event);
        void registerListener(EventsListener<DerivedEvent>* _listener, EventListenerProperties* _properties);
        void unregisterListener(EventsListener<DerivedEvent>* _listener, bool _blockingQueue);
    protected:
    private:
        EventsListener<DerivedEvent>* listenersStart;
        unsigned short queueBlocking;
        std::vector<DerivedEvent>* queuedInstances;
};

template <typename DerivedEvent>
EventHandler<DerivedEvent>::EventHandler()
{
    //ctor
    listenersStart = nullptr;
    queuedInstances = nullptr;
    queueBlocking = 0;
}

template <typename DerivedEvent>
EventHandler<DerivedEvent>::~EventHandler()
{
    //dtor
}

template <typename DerivedEvent>
void EventHandler<DerivedEvent>::trigger(DerivedEvent* _event)
{
    EventsListener<DerivedEvent>* listener = listenersStart;
    while (listener != nullptr)
    {
        listener->trigger(_event);
        listener = listener->next;
    }

    if (queueBlocking == 0)
    {
        if (queuedInstances == nullptr)
            queuedInstances = new std::vector<DerivedEvent>;
        queuedInstances->push_back(*_event);
    }
}

template <typename DerivedEvent>
void EventHandler<DerivedEvent>::registerListener(EventsListener<DerivedEvent>* _listener, EventListenerProperties* _properties)
{
    if (listenersStart != nullptr)
    {
        listenersStart->prev = _listener;
        _listener->next = listenersStart;
    }
    listenersStart = _listener;

    if (_properties->getFlag(eReadQueue) && queuedInstances != nullptr)
    {
        for (auto event = queuedInstances->begin(); event != queuedInstances->end(); event++)
        {
            EventsListener<DerivedEvent>* listener = listenersStart;
            while (listener != nullptr)
            {
                listener->trigger(&*event);
                listener = listener->next;
            }
        }
    }
    if (_properties->getFlag(eClearQueue))
    {
        queuedInstances->clear();
    }
    if (_properties->getFlag(eBlockQueue))
    {
        queueBlocking++;
        if (queuedInstances != nullptr && queuedInstances->size() == 0)
        {
            delete queuedInstances;
            queuedInstances = nullptr;
        }
    }
}

template <typename DerivedEvent>
void EventHandler<DerivedEvent>::unregisterListener(EventsListener<DerivedEvent>* _listener, bool _blockingQueue)
{
    if (_listener->prev != nullptr)
        _listener->prev->next = _listener->next;
    else
    {
        /// This assertion will fail if _listener isn't actually registered
        assert(listenersStart == _listener);
        listenersStart = _listener->next;
    }

    if (_listener->next != nullptr)
        _listener->next->prev = _listener->prev;

    if (_blockingQueue)
        queueBlocking--;
}

#endif // EVENTHANDLER_H
