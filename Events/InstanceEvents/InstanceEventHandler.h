#ifndef INSTANCEEVENTHANDLER_H
#define INSTANCEEVENTHANDLER_H

#include <string>
template <typename EventType>
class InstanceEventListener;

template <typename EventType>
class InstanceEventHandler
{
    public:
        InstanceEventHandler();
        ~InstanceEventHandler();
        void trigger(EventType* _event);
        void registerListener(InstanceEventListener<EventType>* _listener);
        void unregisterListener(InstanceEventListener<EventType>* _listener);
    protected:
    private:
        InstanceEventHandler(const InstanceEventHandler& _rhs); /// Copy constructor is not allowed
        InstanceEventListener<EventType>* listenersStart;
};

#include <Events/InstanceEvents/InstanceEventListener.h>
template <typename EventType>
InstanceEventHandler<EventType>::InstanceEventHandler()
{
    //ctor
    listenersStart = nullptr;
}

template <typename EventType>
InstanceEventHandler<EventType>::~InstanceEventHandler()
{
    //dtor
    InstanceEventListener<EventType>* listener = listenersStart;
    while (listener != nullptr)
    {
        InstanceEventListener<EventType>* prev = listener;
        listener = listener->next;
        prev->handlerDestroyed();
    }
}

template <typename EventType>
void InstanceEventHandler<EventType>::trigger(EventType* _event)
{
    InstanceEventListener<EventType>* listener = listenersStart;
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
}

template <typename EventType>
void InstanceEventHandler<EventType>::registerListener(InstanceEventListener<EventType>* _listener)
{
    if (listenersStart != nullptr)
    {
        listenersStart->prev = _listener;
        _listener->next = listenersStart;
    }
    listenersStart = _listener;
}

template <typename EventType>
void InstanceEventHandler<EventType>::unregisterListener(InstanceEventListener<EventType>* _listener)
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
}

#endif // INSTANCEEVENTHANDLER_H
