#ifndef NAMEDEVENTHANDLER_H
#define NAMEDEVENTHANDLER_H

#include <unordered_map>
#include <string>
template <typename DerivedEvent>
class EventsListener;

template <typename DerivedEvent>
class NamedEventHandler
{
    public:
        NamedEventHandler();
        virtual ~NamedEventHandler();
        void trigger(DerivedEvent* _event, const std::string& _name);
        void registerListener(EventsListener<DerivedEvent>* _listener, const std::string& _name);
        void unregisterListener(EventsListener<DerivedEvent>* _listener, const std::string& _name);
    protected:
    private:
        std::unordered_map<std::string, EventsListener<DerivedEvent>*> listenersStartMap;
};

template <typename DerivedEvent>
NamedEventHandler<DerivedEvent>::NamedEventHandler()
{
    //ctor
}

template <typename DerivedEvent>
NamedEventHandler<DerivedEvent>::~NamedEventHandler()
{
    //dtor
}

template <typename DerivedEvent>
void NamedEventHandler<DerivedEvent>::trigger(DerivedEvent* _event, const std::string& _name)
{
    auto iter = listenersStartMap.find(_name);
    if (iter == listenersStartMap.end()) return;

    EventsListener<DerivedEvent>* listener = iter->second;
    do
    {
        if (!listener->trigger(_event))
        {
            if (listener->prev != nullptr)
                listener->prev->next = listener->next;
            else
            {
                if (listener->next == nullptr)
                {
                    listenersStartMap.erase(iter);
                    break;
                }
                else
                {
                    iter->second = listener->next;
                }
            }
            if (listener->next != nullptr)
                listener->next->prev = listener->prev;
        }
        listener = listener->next;
    }
    while (listener != nullptr);
}

template <typename DerivedEvent>
void NamedEventHandler<DerivedEvent>::registerListener(EventsListener<DerivedEvent>* _listener, const std::string& _name)
{
    auto iter = listenersStartMap.find(_name);
    if (iter->second == nullptr)
    {
        listenersStartMap[_name] = _listener;
    }
    else
    {
        iter->second->prev = _listener;
        _listener->next = iter->second;
    }

}

template <typename DerivedEvent>
void NamedEventHandler<DerivedEvent>::unregisterListener(EventsListener<DerivedEvent>* _listener, const std::string& _name)
{
    if (_listener->prev != nullptr)
        _listener->prev->next = _listener->next;
    else
    {
        /// This assertion will fail if _listener isn't actually registered
        auto iter = listenersStartMap.find(_name);
        assert(iter != listenersStartMap.end());
        iter->second = _listener->next;
    }

    if (_listener->next != nullptr)
        _listener->next->prev = _listener->prev;
}
#endif // NAMEDEVENTHANDLER_H
