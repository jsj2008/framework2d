#ifndef GENERICEVENT_H
#define GENERICEVENT_H

#include <Events/Event.h>
/// FIXME I think I should think of a better way to do this

enum GenericEvents
{
    eFactoryTypeRegister,
};

template <GenericEvents eventType>
class GenericEvent : public Event
{
    public:
        GenericEvent();
        virtual ~GenericEvent();
    protected:
    private:
};

template <GenericEvents eventType>
GenericEvent<eventType>::GenericEvent()
{
    //ctor
}

template <GenericEvents eventType>
GenericEvent<eventType>::~GenericEvent()
{
    //dtor
}

#endif // GENERICEVENT_H
