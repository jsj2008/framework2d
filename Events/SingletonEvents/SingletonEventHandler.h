#ifndef SINGLETONEVENTHANDLER_H
#define SINGLETONEVENTHANDLER_H

#include <vector>
template <typename EventType>
class SingletonEventListener;
template <typename EventType>
class SingletonEvent;

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

template <typename EventType>
class SingletonEventHandler
{
    public:
        static SingletonEventHandler<EventType>& singleton()
        {
            static SingletonEventHandler<EventType> handler;
            return handler;
        }
        void registerListener(SingletonEventListener<EventType>* _listener, EventListenerProperties _properties);
        void unregisterListener(SingletonEventListener<EventType>* _listener, bool _blockingQueue);
    protected:
    private:
        friend class SingletonEvent<EventType>;
        void trigger(EventType* _event);
        SingletonEventHandler();
        ~SingletonEventHandler();
        SingletonEventListener<EventType>* listenersStart;
        unsigned short queueBlocking;
        std::vector<EventType>* queuedInstances;
};

template <typename EventType>
SingletonEventHandler<EventType>::SingletonEventHandler()
{
    //ctor
    listenersStart = nullptr;
    queuedInstances = nullptr;
    queueBlocking = 0;
}

template <typename EventType>
SingletonEventHandler<EventType>::~SingletonEventHandler()
{
    //dtor
}

template <typename EventType>
void SingletonEventHandler<EventType>::trigger(EventType* _event)
{
    SingletonEventListener<EventType>* listener = listenersStart;
    while (listener != nullptr)
    {
        if (!listener->trigger(_event))
        {
            if (listener->prev != nullptr)
                listener->prev->next = listener->next;
            else
                listenersStart = listener->next;
            if (listener->next != nullptr)
                listener->next->prev = listener->prev;
        }
        listener = listener->next;
    }

    if (queueBlocking == 0)
    {
        if (queuedInstances == nullptr)
            queuedInstances = new std::vector<EventType>;
        queuedInstances->push_back(*_event);
    }
}

template <typename EventType>
void SingletonEventHandler<EventType>::registerListener(SingletonEventListener<EventType>* _listener, EventListenerProperties _properties)
{
    if (listenersStart != nullptr)
    {
        listenersStart->prev = _listener;
        _listener->next = listenersStart;
    }
    listenersStart = _listener;

    if (queuedInstances != nullptr)
    {
        if (_properties.getFlag(eReadQueue))
        {
            for (auto event = queuedInstances->begin(); event != queuedInstances->end(); event++)
            {
                SingletonEventListener<EventType>* listener = listenersStart;
                while (listener != nullptr)
                {
                    listener->trigger(&*event);
                    listener = listener->next;
                }
            }
        }
        if (_properties.getFlag(eClearQueue))
        {
            queuedInstances->clear();
        }
    }
    if (_properties.getFlag(eBlockQueue))
    {
        queueBlocking++;
        if (queuedInstances != nullptr && queuedInstances->size() == 0)
        {
            delete queuedInstances;
            queuedInstances = nullptr;
        }
    }
}

template <typename EventType>
void SingletonEventHandler<EventType>::unregisterListener(SingletonEventListener<EventType>* _listener, bool _blockingQueue)
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


#endif // SINGLETONEVENTHANDLER_H
